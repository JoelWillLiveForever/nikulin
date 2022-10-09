/* Условие задачи 2:
 * Вычислить значение числа Пи методом Монте-Карло с точностью 0.0001 */

#include "pch.h"
#include "version.h"
#include "counters.h"

# if 0
#define EPS 0.0001 // точность, c которой нужно найти число Пи

int main()
{
    seed_1024(time(NULL)); // сид для генератора случайных чисел
      
    unsigned long long gp = 0, ap = 0; // хорошие точки и всего точек, соответственно

    long double x = 0, y = 0, len = 0; // координаты точки и её расстояние до центра окружности
    long double prev_pi = -1, curr_pi = 0, e = 1; // предыдущее Пи, текущее Пи и их разность

    // считаем пи, пока не добъёмся нужной точности
    do
    {
        ap++; // считаем всего точек 

        // сгенерируем координаты точки
        x = (long double) next_1024() / (long double) XOR_SHIFT_RAND_MAX;
        y = (long double) next_1024() / (long double) XOR_SHIFT_RAND_MAX;
           
        len = x*x + y*y; // расстояние до центра окружности

        // точка входит в круг
        if (len <= 1.0f) gp++; // хорошие точки
        
        if (ap % 1000 == 0) // раз в 1000 точек сравнить значения Пи, чтобы проверить удовлетворение точности EPS
        {            
            prev_pi = curr_pi;

            curr_pi = 4.0f * (long double) gp / (long double) ap; // вычисляем Пи
            
            e = fabs(curr_pi - prev_pi); // разница между прошлым Пи и текущим Пи (точность)
                                         
            // вывод информации с итерации
            printf("prev_pi = %Lf20; curr_pi = %Lf; eps = %f; gp = %llu; ap = %llu\n", prev_pi, curr_pi, (double) e, gp, ap);
        }
    } 
    while (e > EPS); // как только разница между прошлым Пи и текущим Пи будет > EPS, выйти из цикла

    printf("PI = %Lf;\n", curr_pi); // вывод рассчитанного Пи
    return 0;
}

#else

void print_help_message(char *argv[])
{
    printf("Usage:\n\n"
            " %s [options]\n\n"
            "Options:\n"
            
            " %-40s Show program help info\n"
            " %-40s Show program version\n"
            " %-40s Measure the speed of program execution in given unit\n"
            " %-40s Valid arguments: [seconds | milliseconds | microseconds | nanoseconds] or\n"
            " %-40s                  [sec | msec | usec | nsec] or\n"
            " %-40s                  [ds | ms | us | ns ] or\n"
            " %-40s                  [s | m | u | n ]\n"
            " %-40s Set random generator\n"
            " %-40s Valid arguments: [xor-shift-64 | xor-shift-1024] or\n"
            " %-40s                  [xs64 | xs1024] or\n"
            " %-40s                  [6 | 1]\n\n"

            " %-40s Use all CPU cores for calculating (multi-core processing)\n"
            " %-40s Use GPU (OpenCL) for calculating (GPU processing)\n\n"

            " %-40s Set number of calculated PI numbers for increased accuracy of the final (true) PI numbers\n\n"
            
            " %-40s Set accuracy for calculating PI\n"
            " %-40s Set start points count\n"
            " %-40s Set multiplier to increase points at each calculation iteration\n"
            " %-40s Set maximum number of points AND RUN program in PI convergence check mode\n",
            
            argv[0], 
            "-h, --help", 
            "-v, --version", 
            "-u, --unit Arg (off)", " ", " ", " ", " ", 
            "-g, --generator Arg (xor-shift-64)", " ", " ", " ",
            "-t, --multithread (off)", 
            "-o, --opencl (off)",
            "-n, --number-of-counters Arg (10)",
            "-e, --eps Arg (0.001)", 
            "-s, --start Arg (1000)", 
            "-m, --multiplier Arg (2)", 
            "-p, --max-points Arg (10 000 000)");

    char example1[40],
         example2[40],
         example3[40],
         example4[40];    

    snprintf(example1, sizeof example1, "%s%s", argv[0], " -t");
    snprintf(example2, sizeof example2, "%s%s", argv[0], " -o -e 0.01 -s 1000000");
    snprintf(example3, sizeof example3, "%s%s", argv[0], " -u ms -e 0.0001");
    snprintf(example4, sizeof example4, "%s%s", argv[0], " -s 500 -m 3 -p 20000000");

    printf("\nExamples:\n\n"
            " %-40s Run PI calculation using all CPU cores (pthread)\n"
            " %-40s Run PI calculation using GPU (OpenCL)\n"
            " %-40s Run PI calc with precision 0.0001 and output program elapsed time\n"
            " %-40s Run PI convergence check with start points 500, points multiplier 3 and maximum points 20 000 000\n\n",
            example1, example2, example3, example4);
}

static int verbose_flag;

int main(int argc, char *argv[])
{
//    if ( argc == 1 )
//    {
//        fprintf(stderr, "Error! No arguments!\n");
//        return EXIT_FAILURE;
//    }

    // checked options
    const char* const short_options = "toe:s:n:m:p:u:g:vh";
    const struct option long_options[] = {
        {"verbose",             no_argument,        &verbose_flag, 1},
        {"brief",               no_argument,        &verbose_flag, 0},

        {"multithread",         no_argument,        NULL, 't'},
        {"opencl",              no_argument,        NULL, 'o'},

        {"number-of-counters",  required_argument,  NULL, 'n'},

        {"eps",                 required_argument,  NULL, 'e'},
        {"start",               required_argument,  NULL, 's'},
        {"multiplier",          required_argument,  NULL, 'm'},
        {"max-points",          required_argument,  NULL, 'p'},

        {"unit",                required_argument,  NULL, 'u'},
        {"generator",           required_argument,  NULL, 'g'},
        {"version",             no_argument,        NULL, 'v'},
        {"help",                no_argument,        NULL, 'h'},
        {NULL,                  no_argument,        NULL, 0}
    };

    int option_index = 0;
    int opt;
    
    // флаги для замера времени выполнения
    bool isSeconds      = false,
         isMilliseconds = false,
         isMicroseconds = false,
         isNanoseconds  = false,

         isMultithread  = false,
         isOpenCL       = false,

         use_xs1024     = false;

    // дефолтные значения аргементов main
    uint8_t number_of_counters = 10;

    double eps = 0.001;

    uint32_t start = 1000,
             multiplier = 2,
             max_points = 10000000;

    char *temp;

    while (1)
    {
        opt = getopt_long(argc, argv, short_options, long_options, &option_index);

        // detect the end of the options
        if ( opt == -1 )
            break;
        
        switch ( opt )
        {
            case 0:
                if (long_options[option_index].flag != 0)
                    break;

                printf("Option %s", long_options[option_index].name);

                if (optarg)
                    printf(" with arg %s", optarg);

                printf("\n");
                break;

            case 't':
                isOpenCL = false;
                isMultithread = true;
                break;

            case 'o':
                isMultithread = false;
                isOpenCL = true;
                break;

            case 'n':
                // код конвертации строки в число и проверки взят из:
                // https://stackoverflow.com/questions/14176123/correct-usage-of-strtol

                errno = 0;
                number_of_counters = strtol(optarg, &temp, 0);
                
                if ( temp == optarg || *temp != '\0' ||
                        ((number_of_counters == 0 || number_of_counters == UINT8_MAX) && errno == ERANGE) )
                {
                    fprintf(stderr, "Could not convert '%s' to uint8_t and leftover string is: '%s'\n",
                            optarg, temp);

                    return EXIT_FAILURE;
                }
                break;

            case 'e':
                errno = 0;
                eps = strtod(optarg, &temp);

//                printf("eps: %g\n"
//                        "temp: %s\n",
//                        eps, temp);
        
                if ( temp == optarg || *temp != '\0' ||
                        ((eps == DBL_MIN || eps == DBL_MAX) && errno == ERANGE) )
                {
                    fprintf(stderr, "Could not convert '%s' to double and leftover string is: '%s'\n",
                            optarg, temp);

                    return EXIT_FAILURE;
                } 
                else if ( isinf(eps) )
                {
                    fprintf(stderr, "Could not convert '%s' to double. Very big value (Inf)\n",
                            optarg);

                    return EXIT_FAILURE;
                } 
//                else if ( isnan(eps))
//                {
//                    fprintf(stderr, "Could not convert '%s' to double. Bad value (NaN)\n",
//                            optarg);
//
//                    return EXIT_FAILURE;
//                }

                break;

            case 's':
                errno = 0;
                start = strtol(optarg, &temp, 0);
                
                if ( temp == optarg || *temp != '\0' ||
                        ((start == 0 || start == UINT32_MAX) && errno == ERANGE) )
                {
                    fprintf(stderr, "Could not convert '%s' to uint32_t and leftover string is: '%s'\n",
                            optarg, temp);

                    return EXIT_FAILURE;
                }
                break;

            case 'm':
               errno = 0;
               multiplier = strtol(optarg, &temp, 0);
               
               if ( temp == optarg || *temp != '\0' ||
                       ((multiplier == 0 || multiplier == UINT32_MAX) && errno == ERANGE) )
               {
                   fprintf(stderr, "Could not convert '%s' to uint32_t and leftover string is: '%s'\n",
                           optarg, temp);

                   return EXIT_FAILURE;
               }
               break;

            case 'p':
               errno = 0;
               max_points = strtol(optarg, &temp, 0);
                
               if ( temp == optarg || *temp != '\0' ||
                       ((max_points == 0 || max_points == UINT32_MAX) && errno == ERANGE) )
               {
                   fprintf(stderr, "Could not convert '%s' to uint32_t and leftover string is: '%s'\n",
                           optarg, temp);

                   return EXIT_FAILURE;
               }
               break;

            case 'u':
                // default, milli, micro, nano seconds to check algorithm speed

                if ( !strcmp(optarg, "s") || !strcmp(optarg, "ds") || !strcmp(optarg, "sec") || !strcmp(optarg, "seconds") )
                    isSeconds = true;

                else if ( !strcmp(optarg, "m") || !strcmp(optarg, "ms") || !strcmp(optarg, "msec") || !strcmp(optarg, "milliseconds") )
                    isMilliseconds = true;

                else if ( !strcmp(optarg, "u") || !strcmp(optarg, "us") || !strcmp(optarg, "usec") || !strcmp(optarg, "microseconds") )
                    isMicroseconds = true;

                else if ( !strcmp(optarg, "n") || !strcmp(optarg, "ns") || !strcmp(optarg, "nsec") || !strcmp(optarg, "nanoseconds") )
                    isNanoseconds = true;

                break;

            case 'g':
                // выбор генератора рандомных чисел

                if ( !strcmp(optarg, "6") || !strcmp(optarg, "xs64") || !strcmp(optarg, "xor-shift-64") )
                    use_xs1024 = false;

                else if ( !strcmp(optarg, "1") || !strcmp(optarg, "xs1024") || !strcmp(optarg, "xor-shift-1024") )
                    use_xs1024 = true;

                break;

            case 'v':
                // show program version
                
                printf("%u.%u.%u.%u-%s\n",
                        
                        VERSION_MAJOR,
                        VERSION_MINOR,
                        VERSION_PATCH,
                        VERSION_TWEAK,
                        
                        BUILD_DATE);

                return EXIT_SUCCESS;

            case 'h':
                // show help msg when --help
                
                print_help_message(argv);
                return EXIT_SUCCESS;

            case '?':
            default:
                // if invalid (unrecognized) options

                printf("\n");
                print_help_message(argv);
                return EXIT_FAILURE;
        }
    }

    if (verbose_flag)
        printf("Verbose flag is set\n");

    if ( optind < argc )
    {
        printf("Error! Non-option ARGV-elements: ");

        while (optind < argc)
            printf("%s", argv[optind++]);
        
        printf("\n");
        print_help_message(argv);

        return EXIT_FAILURE;
    }

    double pi = 0;

#ifdef _WIN32
    unsigned long long begin, end;
#else
    struct timeval begin, end;
#endif

    // вариант рассчёта Пи последовательно в одном потоке
    if (!isMultithread && !isOpenCL)
    {
#ifdef _WIN32
        begin = GetTickCount64();
        pi = get_pi_single_thread(number_of_counters, start, multiplier, eps, use_xs1024);
        end = GetTickCount64();
#else
        gettimeofday(&begin, 0);
        pi = get_pi_single_thread(number_of_counters, start, multiplier, eps, use_xs1024);
        gettimeofday(&end, 0);
#endif
    }

    // получить число ядер (потоков) ЦП
    // https://stackoverflow.com/questions/4586405/how-to-get-the-number-of-cpus-in-linux-using-c
    if (isMultithread)
    {
#ifdef _WIN32
        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);
        long number_of_processors = sysInfo.dwNumberOfProcessors; 
#else
        long number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);
#endif

        if (number_of_processors < 1)
        {
            fprintf(stderr, "Could not determine number of CPUs online:\n%s\n", strerror(errno));
            return EXIT_FAILURE;
        }

        printf("\nAvailable CPUs: %ld\n", number_of_processors);
        
#ifdef _WIN32
        begin = GetTickCount64();
        pi = get_pi_multithread(number_of_counters, start, multiplier, eps, number_of_processors, use_xs1024);
        end = GetTickCount64();
#else
        gettimeofday(&begin, 0);
        pi = get_pi_multithread(number_of_counters, start, multiplier, eps, number_of_processors, use_xs1024);
        gettimeofday(&end, 0);
#endif
    }

    if (isOpenCL)
    {
#ifdef _WIN32
        begin = GetTickCount64();
        pi = get_pi_opencl(number_of_counters, start, multiplier, eps, use_xs1024);
        end = GetTickCount64();
#else
        gettimeofday(&begin, 0);
        pi = get_pi_opencl(number_of_counters, start, multiplier, eps, use_xs1024);
        gettimeofday(&end, 0);
#endif
    }

    printf("PI: %f\n", pi);
    
#ifdef _WIN32
    unsigned long long elapsed = (end - begin) * 1000000; // milliseconds * 1000000 = nanoseconds
#else
    unsigned long long elapsed = ((end.tv_sec - begin.tv_sec) * 1000000000) + (end.tv_usec - begin.tv_usec);
#endif

    if (isSeconds)
        printf("Elapsed time: %lld seconds\n", (elapsed / 1000000000));

    if (isMilliseconds)
        printf("Elapsed time: %lld milliseconds\n", (elapsed / 1000000));
    
    if (isMicroseconds)
        printf("Elapsed time: %lld microseconds\n", (elapsed / 1000));
    
    if (isNanoseconds)
        printf("Elapsed time: %lld nanoseconds\n", elapsed);

    return EXIT_SUCCESS;
}

#endif
