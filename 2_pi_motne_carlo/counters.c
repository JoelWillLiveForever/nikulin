#include "counters.h"

struct PIPoints
{
    uint64_t good_points;
    uint64_t all_points;
};

double generatePointsPIMonteCarlo(struct PIPoints *pi_points_arr,
        uint32_t index,
        uint32_t how_much_to_gen)
{
    if (!pi_points_arr) // проверка на нулевой указатель
        return -1;

    struct PIPoints *pi_points = pi_points_arr + index;

    (*pi_points).all_points += how_much_to_gen;

    double x, y;
    uint8_t len;
    
    while (how_much_to_gen--)
    {
        x = next(0, 0);
        y = next(0, 0);

        len = x*x + y*y;
        (*pi_points).good_points += (!len);
    }

    return 4.0 * (double)(*pi_points).good_points / (double)(*pi_points).all_points;
}

double get_pi_single_thread(uint8_t number_of_counters,
        uint32_t start,
        uint32_t multiplier,
        double eps)
{
    struct PIPoints *pi_points_arr = calloc(number_of_counters, sizeof(*pi_points_arr));
    uint32_t i;

    double min_pi, max_pi, pi;

    while (1)
    {
        min_pi = DBL_MAX;
        max_pi = DBL_MIN;

        for (i = 0; i < number_of_counters; i++)
        {
            pi = generatePointsPIMonteCarlo(pi_points_arr, i, start);
            
            if (min_pi > pi)
                min_pi = pi;

            if (max_pi < pi)
                max_pi = pi;
        }

        double e = max_pi - min_pi;
        //printf("eps: %f\n", e);

        if (e < eps)
            break;

        //printf("%f\n", pi);
        //printf("Start: %u\n", start);

        start *= multiplier;
    }

    return pi;
}
