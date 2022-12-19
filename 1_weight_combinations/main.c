/**
 * @file main.c
 * @author Vladimir Nikulin (mail.jorey@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-15
 *
 * Условие задачи 1:
 * Имеется 10 гирь весом 100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000 и 3000 г.
 * Сколькими способами гирями этого набора можно составить вес в V грамм?
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "version.h"
#include "wc_module.h"

/// @brief Ошибка при печати help message
#define EXIT_PRINT_HELP_MSG_FAILURE 2

/// @brief Невозможно прочитать файл с заданным именем
#define EXIT_READ_FILENAME_FAILURE 3

/// @brief Невозможно открыть заданный файл
#define EXIT_OPEN_FILE_FAILURE 4

/// @brief Невозможно выделить память с помощью calloc
#define EXIT_NOMENCLATURE_CALLOC_FAILURE 5

/// @brief Невозможно расширить память с помощью realloc
#define EXIT_NOMENCLATURE_REALLOC_FAILURE 6

/// @brief При чтении файла был встречен отрицацельный вес гири
#define EXIT_NOMENCLATURE_NEGATIVE_WEIGHT_VALUE 7

/// @brief Невозможно прочитать аргумент командной строки '-s, --solution'
#define EXIT_READ_SOLUTION_FAILURE 8

/// @brief Стандартный размер буфера, для malloc, calloc, realloc
#define BUFSIZE 16

/**
 * @brief Печатает help message
 *
 * @param argv Аргументы командной строки
 * @return int Статус код ошибки, по умолчанию 0
 */
int print_help_message( char *argv[] )
{
    int err = printf( "Usage:\n\n"
                      " %s [options]\n\n"
                      "Options:\n"

                      " %-40s Show program help info\n"
                      " %-40s Show program version\n"
                      " %-40s Measure the speed of program execution in given unit\n"
                      " %-40s Valid arguments: [seconds | milliseconds | microseconds | nanoseconds] or\n"
                      " %-40s                  [sec | msec | usec | nsec] or\n"
                      " %-40s                  [ds | ms | us | ns ] or\n"
                      " %-40s                  [s | m | u | n ]\n"
                      " %-40s Choose a solution\n"
                      " %-40s Valid arguments: \"bits\", \"recursive\"\n\n"

                      " %-40s Activate the output of combinations\n\n"

                      " %-40s Select a file for reading the weights nomenclature and target\n\n"
                      //" %-40s Select a file to output the result\n\n"

                      " %-40s Read the weights nomenclature from stdin\n"
                      " %-40s Read the target weight from stdin\n",

                      argv[0],
                      "-h, --help",
                      "-v, --version",
                      "-u, --unit Arg (=off)", " ", " ", " ", " ",
                      "-s, --solution Arg (=bits)", " ",
                      "-c, --show-combinations",
                      "-f, --file Arg (=source_wc.txt)",
                      //"-o, --file-output Arg (=output_wc.txt)",
                      "-n, --nomenclature Arg (=\"100, 200, 300, 400, 500, 1000, 1200, 1400, 1500, 2000, 3000\")",
                      "-t, --target Arg (=11200)"
                    );

    if ( err < 0 )
        return err; // bad exit, if value != 0

    // get executable name
    //char exe[1024];
    //int ret = readlink("/proc/self/exe", exe, sizeof(exe) - 1);
    //if (ret == -1)
    //    return ret;

    //exe[ret] = 0;
    //printf("I am %s\n", exe);

    char example1[40],
         example2[40];

    err = snprintf( example1, sizeof( example1 ), "%s", "./executable" );

    if ( err < 0 || ( unsigned long )err >= sizeof( example1 ) )
        return err; // bad exit, if value != 0

    err = snprintf( example2, sizeof( example2 ), "%s%s", "./executable", " --show-combinations" );

    if ( err < 0 || ( unsigned long )err >= sizeof( example1 ) )
        return err; // bad exit, if value != 0

    err = printf( "\nExamples:\n\n"
                  " %-40s Run with default values\n"
                  " %-40s Run with the output of combinations\n\n",
                  example1, example2 );

    if ( err < 0 )
        return err; // bad exit, if value != 0

    return 0; // success exit
}

static int verbose_flag;

/**
 * @brief Точка входа в программу
 *
 * @param argc Количество переданных аргументов
 * @param argv Сами аргументы
 * @return int Код ошибки, по умолчанию 0
 */
int main( int argc, char *argv[] )
{
    // checked options
    const char *const short_options = "cr:o:m:n:t:u:s:vh";
    const struct option long_options[] =
    {
        {"verbose",             no_argument,        &verbose_flag, 1},
        {"brief",               no_argument,        &verbose_flag, 0},

        {"show-combinations",   no_argument,        NULL, 'c'},
        {"file",                required_argument,  NULL, 'f'},
        //{"file-output",         required_argument,  NULL, 'o'},

        {"nomenclature",        required_argument,  NULL, 'n'},
        {"target",              required_argument,  NULL, 't'},

        {"unit",                required_argument,  NULL, 'u'},
        {"solution",            required_argument,  NULL, 's'},
        {"version",             no_argument,        NULL, 'v'},
        {"help",                no_argument,        NULL, 'h'},
        {NULL,                  no_argument,        NULL, 0}
    };

    int option_index = 0;
    int opt;

    // дефолтный конфиг программы
    bool isSeconds = false,
         isMilliseconds = false,
         isMicroseconds = false,
         isNanoseconds = false,

         isShowCombinations = false, // отобразить комбинации

         isReadFromFile = true;     // читать из файла
    //isOutputToFile = false;

    char *file_source = "source_wc.txt";
    //char file_output[BUFSIZE] = "output_wc.txt";

    unsigned int buffer = 10;
    unsigned int nomenclature_default[10] = { 100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000, 3000 };

    unsigned int *nomenclature = &nomenclature_default[0];
    unsigned int *nomenclature_end = nomenclature + buffer;

    unsigned int target = 0;

    enum Solution solution = BITS;

    char *temp;
    int error_code = 0;

    while ( 1 )
    {
        opt = getopt_long( argc, argv, short_options, long_options, &option_index );

        // detect the end of the options
        if ( opt == -1 )
            break;

        switch ( opt )
        {
            case 0:
                if ( long_options[option_index].flag != 0 )
                    break;

                printf( "Option %s", long_options[option_index].name );

                if ( optarg )
                    printf( " with arg %s", optarg );

                printf( "\n" );
                break;

            case 'c':
                isShowCombinations = true;
                break;

            case 'r':
                // read from file source
                isReadFromFile = true;

                char file_source_tmp[BUFSIZE];
                error_code = snprintf( file_source_tmp, sizeof( file_source_tmp ), "%s", optarg );

                if ( error_code < 0 || ( unsigned long )error_code >= sizeof( file_source_tmp ) )
                {
                    fprintf( stderr, "Error: cannot read source file name: %s, error_code: %d", optarg, error_code );
                    return EXIT_READ_FILENAME_FAILURE;
                }

                file_source = file_source_tmp;
                break;

            //case 'o':
            //    // print result to file output
            //    error_code = snprintf(file_output, BUFSIZE, "%s", optarg);
            //    if (error_code < 0 || error_code >= sizeof file_output)
            //    {
            //        fprintf(stderr, "Error: cannot read output file name: %s, error_code: %d", optarg, error_code);
            //        return EXIT_READ_FILENAME_FAILURE;
            //    }
            //    break;

            case 'n':
                isReadFromFile = false;

                optind--;
                unsigned int weight = 0;

                buffer = BUFSIZE;
                nomenclature = ( unsigned int * )calloc( buffer, sizeof( unsigned int ) );
                nomenclature_end = nomenclature + buffer;

                unsigned int i = 0;

                for ( ; optind < argc && *argv[optind] != '-'; optind++ )
                {
                    if ( nomenclature >= nomenclature_end )
                    {
                        unsigned int new_buffer = buffer + BUFSIZE;
                        unsigned int *tmp;

                        tmp = ( unsigned int * )realloc( nomenclature, new_buffer * sizeof( unsigned int ) );

                        if ( !tmp )
                            return errno;

                        buffer = new_buffer;
                        nomenclature = tmp;
                        nomenclature_end = nomenclature + buffer;
                    }

                    errno = 0;
                    weight = strtol( argv[optind], &temp, 0 );

                    if ( temp == optarg || *temp != '\0' || ( ( weight == 0 || weight == UINT32_MAX ) && errno == ERANGE ) )
                    {
                        fprintf( stderr, "Could not convert '%s' to uint32_t and leftover string is: '%s'\n", argv[optind], temp );
                        return EXIT_FAILURE;
                    }

                    if ( !weight )
                    {
                        fprintf( stderr, "Zero weight met\n" );
                        return EXIT_FAILURE;
                    }

                    *( nomenclature + i ) = weight;
                    i++;
                }

                break;

            case 't':
                errno = 0;
                target = strtol( optarg, &temp, 0 );

                if ( temp == optarg || *temp != '\0' || ( ( target == 0 || target == UINT32_MAX ) && errno == ERANGE ) )
                {
                    fprintf( stderr, "Could not convert '%s' to uint32_t and leftover string is: '%s'\n", optarg, temp );
                    return EXIT_FAILURE;
                }

                break;

            case 's':

                // choose solution
                if ( !strcmp( optarg, "recursive" ) )
                    solution = RECURSIVE;
                else if ( !strcmp( optarg, "bits" ) )
                    solution = BITS;
                else
                {
                    fprintf( stderr, "Cannot read solution arg: %s", optarg );
                    return EXIT_READ_SOLUTION_FAILURE;
                }

                break;

            case 'u':

                // default, milli, micro, nano seconds to check algorithm speed

                if ( !strcmp( optarg, "s" ) || !strcmp( optarg, "ds" ) || !strcmp( optarg, "sec" ) || !strcmp( optarg, "seconds" ) )
                    isSeconds = true;

                else if ( !strcmp( optarg, "m" ) || !strcmp( optarg, "ms" ) || !strcmp( optarg, "msec" ) ||
                          !strcmp( optarg, "milliseconds" ) )
                    isMilliseconds = true;

                else if ( !strcmp( optarg, "u" ) || !strcmp( optarg, "us" ) || !strcmp( optarg, "usec" ) ||
                          !strcmp( optarg, "microseconds" ) )
                    isMicroseconds = true;

                else if ( !strcmp( optarg, "n" ) || !strcmp( optarg, "ns" ) || !strcmp( optarg, "nsec" ) ||
                          !strcmp( optarg, "nanoseconds" ) )
                    isNanoseconds = true;

                break;

            case 'v':
                // show program version
                #if defined(__VERSION_H__)
                fprintf( stdout, "%u.%u.%u.%u-%s %s%s%s\n",

                         VERSION_MAJOR,
                         VERSION_MINOR,
                         VERSION_PATCH,
                         VERSION_TWEAK,

                         BUILD_DATE,

                         #if defined(__GIT_VERSION_H__)
                         "(", GIT_COMMIT_HASH, ")" );
                         #else
                         "", "", "" );
                         #endif

                #else
                fprintf( stdout, "%s\n", "?" );
                #endif
                return EXIT_SUCCESS;

            case 'h':
                // show help msg when --help

                error_code = print_help_message( argv );

                if ( error_code != 0 )
                {
                    fprintf( stderr, "Error: %d", error_code );
                    return EXIT_PRINT_HELP_MSG_FAILURE;
                }

                return EXIT_SUCCESS;

            case '?':
            default:
                // if invalid (unrecognized) options

                printf( "\n" );
                error_code = print_help_message( argv );

                if ( error_code != 0 )
                {
                    fprintf( stderr, "Error: %d", error_code );
                    return EXIT_PRINT_HELP_MSG_FAILURE;
                }

                return EXIT_FAILURE;
        }
    }

    if ( verbose_flag )
        printf( "Verbose flag is set\n" );

    if ( optind < argc )
    {
        printf( "Error: non-option ARGV-elements: " );

        while ( optind < argc )
            printf( "%s", argv[optind++] );

        printf( "\n" );
        print_help_message( argv );

        return EXIT_FAILURE;
    }

    //fprintf(stdout, "file-source: %s\nfile-output: %s\n", file_source, file_output);

    if ( isReadFromFile )
    {
        FILE *file;

        if ( ( file = fopen( file_source, "r" ) ) == NULL )
        {
            // ошибка при открытии файла
            fprintf( stderr, "Error: cannot opening file" );
            return EXIT_OPEN_FILE_FAILURE;
        }

        buffer = BUFSIZE;
        nomenclature = ( unsigned int * )calloc( buffer, sizeof( unsigned int ) ); // номенклатура гирь

        if ( !nomenclature )
            return errno;

        nomenclature_end = nomenclature + buffer;

        unsigned int i = 0;
        int read_int = 0;

        while ( true )
        {
            // читаем данные из файла
            if ( fscanf( file, "%d%*c", &read_int ) == EOF )
            {
                if ( !target )
                    target = nomenclature[i - 1];

                nomenclature[i - 1] = 0;
                break;
            }

            if ( nomenclature >= nomenclature_end )
            {
                unsigned int new_buffer = buffer + BUFSIZE;
                unsigned int *tmp;

                tmp = ( unsigned int * )realloc( nomenclature, new_buffer * sizeof( unsigned int ) );

                if ( !tmp )
                    return errno;

                buffer = new_buffer;
                nomenclature = tmp;
                nomenclature_end = nomenclature + buffer;
            }

            // если обнаружен отрицательный вес -> ошибка
            if ( read_int <= 0 )
            {
                fprintf( stderr, "Error: one or more weights contain negative values" );
                return EXIT_NOMENCLATURE_NEGATIVE_WEIGHT_VALUE;
            }

            nomenclature[i++] = ( unsigned int )
                                read_int; // если всё хорошо, добавить гирю к номенклатуре
        }

        fclose( file );
    }

    if ( !target )
        target = 11200;

    // рассчитываем размер номенклатуры
    unsigned int nomenclature_size = 0;

    for ( unsigned int *ptr = nomenclature; ptr != nomenclature + buffer; ptr++ )
        if ( *ptr )
            nomenclature_size++;

    unsigned int *nomenclature_tmp = ( unsigned int * )calloc( nomenclature_size, sizeof( unsigned int ) );

    for ( unsigned int *ptr = nomenclature_tmp; ptr != nomenclature_tmp + nomenclature_size; ptr++ )
        *ptr = *( nomenclature + ( ptr - nomenclature_tmp ) );

    free( nomenclature );
    nomenclature = nomenclature_tmp;

    #ifdef _WIN32
    unsigned long long begin = 0, end = 0;
    #else
    struct timeval begin, end;
    #endif

    int number_of_combinations = 0;
    unsigned int **combinations = 0;

    #ifdef _WIN32
    begin = GetTickCount64();

    number_of_combinations = get_number_of_combinations( &solution, nomenclature, &nomenclature_size, &target,
                                                         &combinations );

    if ( number_of_combinations == -1 || !combinations )
        return number_of_combinations;

    end = GetTickCount64();
    #else
    gettimeofday( &begin, 0 );

    number_of_combinations = get_number_of_combinations( &solution, nomenclature, &nomenclature_size, &target,
                                                         &combinations );

    if ( number_of_combinations == -1 || !combinations )
        return number_of_combinations;

    gettimeofday( &end, 0 );
    #endif

    fprintf( stdout, "%d\n", number_of_combinations );

    if ( isShowCombinations )
    {
        for ( unsigned int **combination = combinations, **combination_end = combinations + number_of_combinations;
                combination != combination_end; combination++ )
        {
            fprintf( stdout, "%s\n", " " );

            for ( unsigned int *weight = *combination, *weight_end = *combination + nomenclature_size; weight != weight_end;
                    weight++ )
                if ( *weight )
                    fprintf( stdout, "%u%s", *weight, " " );
        }

        fprintf( stdout, "%s\n", " " );
    }

    #ifdef _WIN32
    unsigned long long elapsed = ( end - begin ) * 1000000; // milliseconds * 1000000 = nanoseconds
    #else
    unsigned long long elapsed = ( ( end.tv_sec - begin.tv_sec ) * 1000000000 ) + ( end.tv_usec - begin.tv_usec );
    #endif

    if ( isSeconds )
        printf( "Elapsed time: %f seconds\n", ( elapsed / ( double )1000000000 ) );

    if ( isMilliseconds )
        printf( "Elapsed time: %f milliseconds\n", ( elapsed / ( double )1000000 ) );

    if ( isMicroseconds )
        printf( "Elapsed time: %f microseconds\n", ( elapsed / ( double )1000 ) );

    if ( isNanoseconds )
        printf( "Elapsed time: %f nanoseconds\n", ( double )elapsed );

    // clear memory
    free( nomenclature );

    return EXIT_SUCCESS;
}
