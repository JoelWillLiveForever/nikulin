/* Условие задачи 2:
 * Вычислить значение числа Пи методом Монте-Карло с точностью 0.0001 */

#include "stdafx.hpp"
#include "true_pi_selector_class.hpp"

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
                << std::string(HELP_INDENT, ' ') << "-h, --help" << "\t\t\tShow program help info" << "\n"
                << std::string(HELP_INDENT, ' ') << "-v, --version" << "\t\tDisplay program version" << "\n"
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
                std::cout << "EPS is not a float number: " << argv[1] << std::endl;
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

    return EXIT_SUCCESS;
}
