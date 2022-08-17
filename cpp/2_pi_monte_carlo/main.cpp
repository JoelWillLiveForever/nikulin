/* Условие задачи 2:
 * Вычислить значение числа Пи методом Монте-Карло с точностью 0.0001 */

#include "stdafx.hpp"
#include "true_pi_selector_class.hpp"
#include "pi_convergence_check_class.hpp"

#include <sstream>

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
                << std::string(HELP_INDENT, ' ') << argv[0] << " eps_value\n"
                << "\nOptions:\n"
                << std::string(HELP_INDENT, ' ') << "-h, --help" << "\t\t\t\t\t\t\t\t\tShow program help info\n"
                << std::string(HELP_INDENT, ' ') << "-v, --version" << "\t\t\t\t\t\t\t\tDisplay program version\n"
                << std::string(HELP_INDENT, ' ') << "-c [total_pi, points_start, points_multiplier, max_points],\n"
                << std::string(HELP_INDENT, ' ') << "--check [total_pi, points_start, points_multiplier, max_points]" << "\t\tRun in PI convergence check mode\n"
                << std::endl;
        }
        else 
        {
            // в этом случае там просто значение EPS
            char *endptr = 0;
            strtod(argv[1], &endptr);

            if ( *endptr != '\0' || endptr == argv[1] )
            {
                // bad double
                std::cout << "Error! EPS is not a float number: " << argv[1] << std::endl;
                return EXIT_FAILURE;
            }
            
            // good double
            double eps = std::strtod(argv[1], NULL);

            // Объект класса TruePISelector для вычисления Пи
            TruePISelector selector(5, eps);
            double result = selector.select_pi();

            // вывод рассчитанного Пи
            std::cout << "\nPI = " << result << std::endl;
        }
    }
    else if ( argc == 6 )
    {
        if ( std::string(argv[1]) == "-c" || std::string(argv[1]) == "--check" )
        {
            unsigned int total_pi = 0, points_start = 0, points_multiplier = 0, max_points = 0;


            for (int i = 2; i < argc; i++)
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

            PIConvergenceCheck checker(total_pi, points_start, points_multiplier, max_points);
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
