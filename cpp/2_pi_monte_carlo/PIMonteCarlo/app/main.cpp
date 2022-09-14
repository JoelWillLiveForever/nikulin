/* Условие задачи 2:
 * Вычислить значение числа Пи методом Монте-Карло с точностью 0.0001 */

#include "../include/pch.hpp"
#include "../include/true_pi_selector_class.hpp"
#include "../include/pi_convergence_check_class.hpp"

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
