/* Условие задачи 2:
 * Вычислить значение числа Пи методом Монте-Карло с точностью 0.0001 */

#include <stdio.h>
#include <time.h>
#include <math.h>
#include "xor_shift.h"

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
            printf("prev_pi = %Lf20; curr_pi = %Lf; eps = %f; gp = %lu; ap = %lu\n", prev_pi, curr_pi, (double) e, gp, ap);
        }
    } 
    while (e > EPS); // как только разница между прошлым Пи и текущим Пи будет > EPS, выйти из цикла

    printf("PI = %Lf;\n", curr_pi); // вывод рассчитанного Пи
    return 0;
}
