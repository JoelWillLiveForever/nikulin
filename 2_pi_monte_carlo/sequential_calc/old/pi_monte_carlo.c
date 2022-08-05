/* Условие задачи 2:
 * Вычислить значение числа Пи методом Монте-Карло с точностью 0.0001 */

#include <stdio.h>
#include <time.h>
#include <math.h>
#include "xor_shift.h"

#define EPS 0.00001 // точность, c которой нужно найти число Пи
#define NUMBERS 10 // количество чисел Пи, которые будут рассчитываться независимо для сравнения их точности

int main()
{
    unsigned long m_time = time(NULL);
    seed_1024(m_time); // начало последовательности от текущего системного времени (seed), чтобы случайные значения не повторялись

    printf("Time = %lu;\n", m_time);

    unsigned long gp[NUMBERS] = {0}, ap = 0;
    unsigned long i;

    double x = 0, y = 0, len = 0, eps = EPS + 1;
    double prev_avg_pi = -1, curr_avg_pi = 0;

    // считаем пи, пока не добъёмся нужной точности
    do
    {

        ap++; // всего точек, для всех Пи одинаково

        for (i = 0; i < NUMBERS; i++)
        {
            // пи
            x = (double) next_1024() / (double) XOR_SHIFT_RAND_MAX;
            y = (double) next_1024() / (double) XOR_SHIFT_RAND_MAX;
           
            len = sqrt(x*x + y*y); 

            // точка входит в круг
            if (len <= 1) gp[i]++;
        }
         
        if (ap % 10000 == 0)
        {            
            //prev_avg_pi = curr_avg_pi;
            //curr_avg_pi = 0;
            eps = 0;
            for (i = 0; i < NUMBERS; i++)
            {
                curr_avg_pi = 4.0f * (double) gp[i] / (double) ap;

                (i % 2 == 0)
                    ? (eps += curr_avg_pi)
                    : (eps -= curr_avg_pi);

                eps = fabs(eps);
            }
                //curr_avg_pi += 4.0f * ((double) gp[i] / (double) ap);
            //curr_avg_pi /= (double) NUMBERS;

            //eps = fabs(curr_avg_pi - prev_avg_pi);

            printf("prev_avg_pi = %f; curr_avg_pi = %f; eps = %f; ap = %lu\n", prev_avg_pi, curr_avg_pi, eps, ap);
        }
    } 
    while (eps > EPS);
    
    printf("ap = %lu; prev_avg_pi = %f; curr_avg_pi = %f;\n", ap, prev_avg_pi, curr_avg_pi);
    for (i = 0; i < NUMBERS; i++)
        printf("gp[%d] pi = %f;\n", i, 4.0f * (double) gp[i] / (double) ap);

    return 0;
}
