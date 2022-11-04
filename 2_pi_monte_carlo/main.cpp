/* Условие задачи 2:
 * Вычислить значение числа Пи методом Монте-Карло с точностью 0.0001 */

#include "version.h"

#include "true_pi_selector_class.hpp"
#include "pi_convergence_check_class.hpp"

//#include "spdlog/spdlog.h"
//#include "spdlog/sinks/basic_file_sink.h" // support for basic file logging
//#include "spdlog/sinks/rotating_file_sink.h" // support for rotating file logging

#if 0

#define HELP_INDENT 4

int main(int argc, char *argv[])
{
    if ( argc == 2 )
    {
        if ( std::string(argv[1]) == "-v" || std::string(argv[1]) == "--version" )
        {
            std::cout << "1.0.0.0" << std::endl;
        }
        else if ( std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help" )
        {
            std::cout << "This is a Monte Carlo search engine for a PI number. Usage:\n"
                << std::string(HELP_INDENT, ' ') << argv[0] <<" [options]\n"
                << "\nOptions:\n"
                << std::string(HELP_INDENT, ' ') << "-h, --help" << "\t\t\t\t\t\t\t\t\tShow program help info\n"
                << std::string(HELP_INDENT, ' ') << "-v, --version" << "\t\t\t\t\t\t\t\tDisplay program version\n"
                << std::string(HELP_INDENT, ' ') << "-c [total_pi, points_start, points_multiplier, max_points, eps],\n"
                << std::string(HELP_INDENT, ' ') << "--check [total_pi, points_start, points_multiplier, max_points, eps]" << "\tRun PI convergence check\n"
                << std::string(HELP_INDENT, ' ') << "-s [total_pi, points_start, points_multiplier, eps],\n"
                << std::string(HELP_INDENT, ' ') << "--select [total_pi, points_start, points_multiplier, eps]" << "\tRun PI calculation with given precision (eps)\n"
                << std::endl;
        }
        else 
        {
            std::cout << "Error! Bad arguments!\n";
            return EXIT_FAILURE;
        }
    }
    else if ( argc == 6 )
    {
        if ( std::string(argv[1]) == "-s" || std::string(argv[1]) == "--select" )
        {
            unsigned int total_pi = 0, points_start = 0, points_multiplier = 0;
            double eps = 0;

            for (int i = 2; i < argc - 1; i++)
            { 
                std::string arg = argv[i];

                try
                {
                    std::size_t pos;
                    switch (i)
                    {
                        case 2:
                            total_pi = std::stoi(arg, &pos);
                            break;
                        case 3:
                            points_start = std::stoi(arg, &pos);
                            break;
                        case 4:
                            points_multiplier = std::stoi(arg, &pos);
                            break;
                    }
                    
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

            eps = atof(argv[5]);
            
            std::cout << "PI is now being calculated!\n";
                
            TruePISelector selector(total_pi, points_start, points_multiplier, eps);

            auto start = std::chrono::high_resolution_clock::now();
            double pi = selector.select_pi();
            auto stop = std::chrono::high_resolution_clock::now();

            // рассчитываем время затраченное на выполнение алгоритма в функции selector.select_pi()
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

            std::cout << "PI is " << pi << '\n';
            std::cout << "Elapsed time: " << duration.count() << " ms" << std::endl;
        }
    }
    else if ( argc == 7 )
    {
        if ( std::string(argv[1]) == "-c" || std::string(argv[1]) == "--check" )
        {
            unsigned int total_pi = 0, points_start = 0, points_multiplier = 0, max_points = 0;
            double eps = 0;

            for (int i = 2; i < argc - 1; i++)
            { 
                std::string arg = argv[i];

                try
                {
                    std::size_t pos;
                    switch (i)
                    {
                        case 2:
                            total_pi = std::stoi(arg, &pos);
                            break;
                        case 3:
                            points_start = std::stoi(arg, &pos);
                            break;
                        case 4:
                            points_multiplier = std::stoi(arg, &pos);
                            break;
                        case 5:
                            max_points = std::stoi(arg, &pos);
                            break;
                    }
                    
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

            eps = atof(argv[6]);

            PIConvergenceCheck checker(total_pi, points_start, points_multiplier, max_points, eps);
            checker.convergence_check();
        }
    }
    else
    {
        std::cerr << "Error! Bad arguments!" << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

#else

//struct SelectOptionArgs
//{
//    unsigned int    total;
//    unsigned int    start;
//    double          multiplier;
//    double          eps;
//};
//
//inline std::istream& operator >> (std::istream& in, SelectOptionArgs& args)
//{
//    int expected = 4;
//
//    while ( expected-- )
//    {
//        std::cout << "Expected: " << expected << '\n';
//        switch( expected )
//        {
//            case 3:
//                unsigned int total;
//                in >> total;
//
//                args.total = total;
//                break;
//
//            case 2:
//                unsigned int start;
//                in >> start;
//
//                args.start = start;
//                break;
//
//            case 1:
//                double multiplier;
//                in >> multiplier;
//
//                args.multiplier = multiplier;
//                break;
//
//            case 0:
//                double eps;
//                in >> eps;
//
//                args.eps = eps;
//                break;
//
//            //default:
//            //    throw std::runtime_error("Invalid arguments for \"SelectOptionArgs\" struct");
//        }
//    }
//    
//    return in;
//}

namespace po = boost::program_options;
std::string program_name = "?";

int main(int argc, char **argv)
{
    program_name = std::string(argv[0]);
    program_name = program_name.substr(program_name.find_last_of("/\\") + 1);   // вытягиваем имя проги из argv[0]

    std::shared_ptr<spdlog::logger> logger = nullptr;
    try
    {
        // Create basic file logger (not rotated)
        //logger = spdlog::basic_logger_mt("main.cpp", "logs/basic.txt");

        // create a file rotating logger with 5mb size max and 3 rotated files
        std::string file_name = std::string("logs/") + program_name + std::string(".txt");
        unsigned long file_size = 5242880UL;

        logger = spdlog::rotating_logger_mt("main.cpp", file_name, file_size, 3);
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    logger->info("Logger init");

    po::options_description generic( "Generic options" );
    generic.add_options()
        ( "help,h",     "Get help message" )
        ( "version,v",  "Get program version" )
    ;

    po::options_description config( "Configuration" );
    config.add_options()
        ("total,t",         po::value<unsigned int>()->default_value(4),    "Set number of calculated PI")
        ("start,s",         po::value<unsigned int>()->default_value(1000), "Set starting numbers of points")
        ("multiplier,m",    po::value<double>()->default_value(2.0),        "Set points multiplier")
        ("max-points",      po::value<unsigned int>()->default_value(0),    "Set maximum number of points AND RUN program in PI convergence check mode")
        ("eps,e",           po::value<double>()->default_value(0.01),       "Set calculation accuracy")
//        ( "select,s", po::value<std::vector<unsigned int>>()->multitoken()->value_name("\"total_pi, points_start, points_multiplier, eps\""),  "Run PI calculation" )
//        ( "select,s", po::value<SelectOptionArgs>()->value_name("\"total_pi, points_start, points_multiplier, eps\""),  "Run PI calculation" )
//        ( "check,c",    "Run PI convergence check" )
    ;

    po::options_description desc;
    desc.add(generic).add(config);

    po::variables_map vm;
    po::store( po::command_line_parser( argc, argv ).options( desc ).allow_unregistered().run(), vm );
    po::notify( vm );

//    if ( vm.count( "help" ) || argc == 1 )
    if ( vm.count( "help" ) )
    {
        std::cout << desc << '\n';

        logger->info("Print help message");

        return EXIT_SUCCESS;
    }

    if ( vm.count( "version" ) )
    {
        std::string version = "?";
        #if defined(__VERSION_H__)
        version = VERSION_MAJOR + "."
            + VERSION_MINOR + "."
            + VERSION_PATCH + "."
            + VERSION_TWEAK + "-"
            + BUILD_DATE;
        #elif defined(__GIT_VERSION_H__)
        version = GIT_COMMIT_HASH;
        #endif
        std::cout << version << std::endl;

        logger->info("Print program version: {}", version);

        return EXIT_SUCCESS;
    }
    
    unsigned int total_pi       = vm["total"].as<unsigned int>(),
                 points_start   = vm["start"].as<unsigned int>(),
                 max_points     = vm["max-points"].as<unsigned int>();

    double points_multiplier    = vm["multiplier"].as<double>(),
           eps                  = vm["eps"].as<double>();

    logger->info("Command line arguments:\ntotal_pi: {}\npoints_start: {}\nmax_points: {}\npoints_multiplier: {}\neps: {}\n", 
        total_pi, points_start, max_points, points_multiplier, eps);

    if ( vm.count("max-points") && max_points )
    {
        // запустить в режиме проверки сходимости
 
        std::cout << "...Checking\n";
        logger->info("...Checking");

        PIConvergenceCheck checker(total_pi, points_start, points_multiplier, max_points, eps);
        
        auto start = std::chrono::high_resolution_clock::now();
        checker.convergence_check();
        auto stop = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << "Elapsed time: " << duration.count() << " ms" << std::endl;

        return EXIT_SUCCESS;
    }
    
    // запуск в режиме рассчёта Пи (по-умолчанию)

//    std::cout << "Total PI: " << total_pi << '\n'
//        << "Points start: " << points_start << '\n'
//        << "Multiplier: "   << points_multiplier << '\n'
//        << "Eps:"           << eps << '\n'
//        << "Max points " << max_points << '\n';

    std::cout << "...Processing\n";
    logger->info("...Processing");
        
    TruePISelector selector(total_pi, points_start, points_multiplier, eps);

    auto start = std::chrono::high_resolution_clock::now();
    double pi = selector.select_pi();
    auto stop = std::chrono::high_resolution_clock::now();

    // рассчитываем время затраченное на выполнение алгоритма в функции selector.select_pi()
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "PI is " << pi << '\n';
    std::cout << "Elapsed time: " << duration.count() << " ms" << std::endl;

    logger->info("Result:\npi: {}\nelapsed time: {}\n",
        pi, duration.count());

//    if ( vm.count( "select" ) )
//    {
//        //std::vector<unsigned int> args;
//        //if ( !vm["select"].empty() && (args = vm["select"].as<std::vector<unsigned int>>()).size() == 4 )
//        //{
//
//        SelectOptionArgs args = vm["select"].as<SelectOptionArgs>();
//
//            unsigned int total_pi = args.total, points_start = args.start, points_multiplier = args.multiplier;
//            double eps = args.eps;
//
////            for (int i = 2; i < argc - 1; i++)
////            { 
////                std::string arg = argv[i];
////    
////                try
////                {
////                    std::size_t pos;
////                    switch (i)
////                    {
////                        case 2:
////                            total_pi = std::stoi(arg, &pos);
////                            break;
////                        case 3:
////                            points_start = std::stoi(arg, &pos);
////                            break;
////                        case 4:
////                            points_multiplier = std::stoi(arg, &pos);
////                            break;
////                    }
////                    
////                    if ( pos < arg.size() )
////                    {
////                        std::cerr << "Error! Trailing characters after number: " << arg << '\n';
////                        return EXIT_FAILURE;
////                    }
////                }
////                catch ( std::invalid_argument const &ex )
////                {
////                    std::cerr << "Error! Invalid number: " << arg << '\n';
////                    return EXIT_FAILURE;
////                }
////                catch ( std::out_of_range const &ex )
////                {
////                    std::cerr << "Error! Number out of range: " << arg << '\n';
////                    return EXIT_FAILURE;
////                }
////            }
////    
////            eps = atof(argv[5]);
//            
//            std::cout << "...Processing\n";
//                
//            TruePISelector selector(total_pi, points_start, points_multiplier, eps);
//    
//            auto start = std::chrono::high_resolution_clock::now();
//            double pi = selector.select_pi();
//            auto stop = std::chrono::high_resolution_clock::now();
//    
//            // рассчитываем время затраченное на выполнение алгоритма в функции selector.select_pi()
//            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
//    
//            std::cout << "PI is " << pi << '\n';
//            std::cout << "Elapsed time: " << duration.count() << " ms" << std::endl;
//            
//            return EXIT_SUCCESS;
//        //}
//        //else
//        //{
//        //    std::cerr << "Bad arguments!" << '\n';
//        //    return EXIT_FAILURE;
//        //}
//    }

//    if ( vm.count( "check" ) )
//    {
//        return EXIT_SUCCESS;
//    }

    return EXIT_SUCCESS;
}

#endif