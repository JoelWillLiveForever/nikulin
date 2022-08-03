/* Условие задачи 2:
 * Вычислить значение числа Пи методом Монте-Карло с точностью 0.0001 */

#include <stdio.h>
#include <time.h>
#include <math.h>
#include "xor_shift.h"

#define EPS 0.0001f // точность, c которой нужно найти число Пи

int main()
{
    unsigned long m_time = time(NULL);
    seed_1024(m_time);
      
    unsigned long long gp = 0, ap = 0;

    float e = -1;
    long double x = 0, y = 0, len = 0;
    long double prev_pi = -1, curr_pi = 0;

    // считаем пи, пока не добъёмся нужной точности
    do
    {
        ap++; // всего точек, для всех Пи одинаково

        // пи
        x = (long double) next_1024() / (long double) XOR_SHIFT_RAND_MAX;
        y = (long double) next_1024() / (long double) XOR_SHIFT_RAND_MAX;
           
        len = x*x + y*y; 

        // точка входит в круг
        if (len <= 1.0f) gp++;
        
        if (ap % 1000000 == 0)
        {            
            prev_pi = curr_pi;

            curr_pi = 4.0f * (long double) gp / (long double) ap;
            curr_pi = ((int) (curr_pi / EPS)) * EPS; // отбрасываем лишнюю дробную часть
            
            e = fabs(curr_pi - prev_pi);
            e = ((int) (e / EPS)) * EPS;
            printf("prev_pi = %Lf20; curr_pi = %Lf; eps = %f; gp = %lu; ap = %lu\n", prev_pi, curr_pi, e, gp, ap);
        }
    } 
    while (e != EPS);

    printf("PI = %Lf;\n", curr_pi);
    return 0;
}
