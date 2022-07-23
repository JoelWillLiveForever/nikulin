#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define CL_TARGET_OPENCL_VERSION 200
#include <CL/cl.h>

#define MAX_POINTS 99999999.0

int main()
{
    srand((unsigned int) time(NULL)); // типа обнуление сида, чтобы случайные значения не повторялись
    
    int points = 0;
    int count = 0;

    while (points < MAX_POINTS)
    {
        double x = (double) rand() / (double) RAND_MAX;
        double y = (double) rand() / (double) RAND_MAX;

        double length = sqrt(x*x + y*y);

        if (length <= 1.0)
            count++;

        //printf("X = %f; Y = %f; LENGTH = %f\n", x, y, length);
        points++;
    }

    printf("COUNT = %d\n", count);

    double pi = 4.0 * (((double) count) / MAX_POINTS);
    printf("PI = %f\n", pi);

    return 0;
}
