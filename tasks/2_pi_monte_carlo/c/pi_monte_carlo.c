/* Условие задачи 2:
 * Вычислить значение числа Пи методом Монте-Карло с точностью 0.0001 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ALL_POINTS 2500000000

int main()
{
    srand((unsigned int) time(NULL)); // начало последовательности от текущего системного времени (seed), чтобы случайные значения не повторялись
  
    unsigned int curr_point = 0;
    unsigned int good_points = 0;
    while (curr_point < ALL_POINTS)
    {
        double x = (double) rand() / (double) RAND_MAX;
        double y = (double) rand() / (double) RAND_MAX;

        double length = sqrt(x*x + y*y);

        if (length <= 1.0)
            good_points++;

        // printf("X = %f; Y = %f; LENGTH = %f\n", x, y, length);
        curr_point++;
    }

    printf("All points: %u\n", ALL_POINTS);
    printf("Good points: %u\n", good_points);

    double pi = 4.0 * (((double) good_points) / ALL_POINTS);
    printf("PI = %f\n", pi);

    return 0;
}
