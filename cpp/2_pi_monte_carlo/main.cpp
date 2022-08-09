/* Условие задачи 2:
 * Вычислить значение числа Пи методом Монте-Карло с точностью 0.0001 */

#include "stdafx.hpp"
#include "true_pi_selector_class.hpp"

#define EPS 1e-4 // точность, c которой нужно найти число Пи

int main()
{
    // Объект класса TruePISelector для вычисления Пи
    TruePISelector selector(5, EPS);
    double result = selector.select_pi();

    // вывод рассчитанного Пи
    std::cout << "\nPI = " << result << std::endl;

    return 0;
}
