/* Условие задачи 1:
 * Имеется 10 гирь весом 100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000 и 3000 г.
 * Сколькими способами гирями этого набора можно составить вес в V грамм? */ 

#include "../include/pch.hpp"
#include "../include/weight_combinator_class.hpp"

// значения флагов для использования в аргументах main
//const std::vector<std::string> flag_help            = {"-h", "--help"},
//                               flag_version         = {"-v", "--version"},
//                               flag_nomenclature    = {"-n", "--nomenclature"},
//                               flag_target          = {"-t", "--target"},
//                               flag_file            = {"-f", "--file"},
//                               flag_milliseconds    = {"-m", "--ms", "--msec", "--milliseconds"},
//                               flag_microseconds    = {"-u", "--us", "--usec", "--microseconds"};

static int verbose_flag;

int main(int argc, char *argv[])
{
    // empty args checking
    if ( argc == 1 )
    {
        std::cout 
            << "Error! No arguments!"
            << std::endl;

        return EXIT_FAILURE;
    }

    // checked options
    const char* const short_options = "f:n:t:u:vh";
    const struct option long_options[] = {
        {"verbose",         no_argument,        &verbose_flag, 1},
        {"brief",           no_argument,        &verbose_flag, 0},

        {"file",            required_argument,  nullptr, 'f'},
        {"nomenclature",    required_argument,  nullptr, 'n'},
        {"target",          required_argument,  nullptr, 't'},
        {"unit",            required_argument,  nullptr, 'u'},
        {"version",         no_argument,        nullptr, 'v'},
        {"help",            no_argument,        nullptr, 'h'},
        {nullptr,           no_argument,        nullptr, 0}
    };

    int option_index = 0;
    int opt;
    
    // номенклатура весов и целевой вес
    WeightCombinator::Weights nomenclature;
    int target = 0;
    
    // флаги для замера времени выполнения
    bool isMilliseconds  = false,
         isMicroseconds  = false,
         isNanoseconds   = false;

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

                std::cout << "Option " << long_options[option_index].name;

                if (optarg)
                    std::cout << " with arg " << optarg;
                std::cout << std::endl;

                break;

            case 'f':
                {
                    // dumbbells nomenclature & target weight source file path
                    if ( !nomenclature.empty() )
                        nomenclature.clear();

                    if ( target != -1 )
                        target = -1;

                    std::ifstream infile;
                    infile.open(optarg, std::ios::in);

                    if ( !infile )
                    {
                        std::cout << "Error! File bad or empty!" << std::endl;
                        return EXIT_FAILURE;
                    }

                    std::string str;
                    while ( std::getline(infile,  str) )
                    {
                        if ( str.size() > 0 )
                        {
                            std::stringstream ss(str);
                            for (int i; ss >> i;)
                            {
                                nomenclature.push_back(i);
    
                                if ( ss.peek() == ',' || ss.peek() == ' ' )
                                    ss.ignore();
                            }
                        }
                    }

                    infile.close();

                    target = nomenclature.back();
                    nomenclature.pop_back();
                }
                break;

            case 'n':
                {
                    // dumbbells nomenclature
                    std::string args = optarg;

                    if ( !nomenclature.empty() )
                        nomenclature.clear();

                    if ( args.size() > 0 )
                    {
                        std::stringstream ss(args);

                        for (int i; ss >> i;)
                        {
                            nomenclature.push_back(i);

                            if ( ss.peek() == ',' || ss.peek() == ' ' )
                                ss.ignore();
                        }
                    }
                }
                break;

            case 't':
                {
                    // target weight             
                    std::string arg = optarg;
                    
                    //if ( target != -1 )
                    //    target = -1;

                    try
                    {
                        std::size_t pos;
                        target = std::stoi(arg, &pos);
                        
                        if ( pos < arg.size() )
                        {
                            std::cerr << "Error! Trailing characters after number: " << arg << '\n';
                            return EXIT_FAILURE;
                        }
                    }
                    catch ( std::invalid_argument const &ex )
                    {
                        std::cerr << "Error! Invalid number: " << arg << '\n';
                        return EXIT_FAILURE;
                    }
                    catch ( std::out_of_range const &ex )
                    {
                        std::cerr << "Error! Number out of range: " << arg << '\n';
                        return EXIT_FAILURE;
                    }
                }
                break;

            case 'u':
                {
                    // milli, micro, nano seconds to check algorithm speed
                    std::string arg = optarg; 

                    if ( arg == "m" || arg == "ms" || arg == "msec" || arg == "milliseconds" )
                        isMilliseconds = true;
    
                    else if ( arg == "u" || arg == "us" || arg == "usec" || arg == "microseconds" )
                        isMicroseconds = true;
    
                    else if ( arg == "n" || arg == "ns" || arg == "nsec" || arg == "nanoseconds" )
                        isNanoseconds = true;
                }
                break;

            case 'v':
                {
                    // show program version
                
                    std::cout 
                        << "1.0.0.0" 
                        << std::endl;
                }
                break;

            case 'h':
                {
                    // show help msg when --help
                    const int cout_w = 60;

                    std::cout << std::left
                        << "Usage:"
                        << "\n " << argv[0] <<" [options][operands]"

                        << "\n\nOptions:"
                    
                        << std::setw(cout_w)
                        << "\n -h, --help"
                        << "\tShow program help info"
                    
                        << std::setw(cout_w)
                        << "\n -v, --version" 
                        << "\tDisplay program version"

                        << std::setw(cout_w)
                        << "\n\n -f [PATH/TO/FILE],"
                        << std::setw(cout_w)
                        << "\n --file [PATH/TO/FILE]" 
                        << "\tRead dumbbells nomenclature and target weigth from [FILE]"
                    
                        << std::setw(cout_w)                    
                        << "\n\n -n [WEIGHT_1, WEIGHT_2, ... WEIGHT_N],"
                        << std::setw(cout_w)
                        << "\n --nomenclature [WEIGHT_1, WEIGHT_2, ... WEIGHT_N]"
                        << "\tSet dumbbells nomenclature from command line"
                    
                        << std::setw(cout_w)                    
                        << "\n\n -t [TARGET_WEIGHT],"
                        << std::setw(cout_w)
                        << "\n --target [TARGET_WEIGHT]"
                        << "\tSet target weight from command line"
                    
                        << std::setw(cout_w)                    
                        << "\n\n -u [m | u | n],"
                        << std::setw(cout_w)
                        << "\n --unit [ms | us | ns],"
                        << std::setw(cout_w)
                        << "\n --unit [msec | usec | nsec],"
                        << std::setw(cout_w)
                        << "\n --unit [milliseconds | microseconds | nanoseconds]"
                        << "\tMeasure the speed of program execution in given unit"
                     
                        << std::endl;
                }        
                break;

            case '?':
            default:
                // if invalid (unrecognized) options

                break;
        }
    }

    if (verbose_flag)
        std::cout << "Verbose flag is set" << std::endl;

    if ( optind < argc )
    {
        std::cout << "Error! Non-option ARGV-elements: ";

        while (optind < argc)
            std::cout << argv[optind++];
        std::cout << std::endl;

        //return EXIT_FAILURE;
    }

    if (target)
    {
        // вектор для хранения найденных комбинаций
        WeightCombinator::Combinations combinations;
    
        // создаём объект класса WeightsCombinator и ищем все комбинации
        WeightCombinator combinator;
        
        try
        {
            auto start = std::chrono::high_resolution_clock::now();
            combinator.combine(target, combinations, nomenclature);
            auto stop = std::chrono::high_resolution_clock::now();
    
            // выводим результат
            unsigned int counter = 0;
            std::cout << "Amount combinations: " << combinations.size() << '\n';
            for (auto combination: combinations)
            {
                std::cout << ++counter << ": ";
                for (auto el: combination)
                    std::cout << el << ' ';
                std::cout << '\n';
            }
        
            // выводим время выполнения, если были соотв. флаги
            if ( isMilliseconds )
            {
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                std::cout << "Elapsed time: " << duration.count() << " ms" << std::endl;
            }
            else if ( isMicroseconds )
            {
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                std::cout << "Elapsed time: " << duration.count() << " us" << std::endl;
            }
            else if ( isNanoseconds )
            {
                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
                std::cout << "Elapsed time: " << duration.count() << " ns" << std::endl;
            }
        }
        catch ( std::invalid_argument const &ex )
        {
            std::cerr << ex.what() << std::endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
