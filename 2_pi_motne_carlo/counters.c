#include "counters.h"

double get_pi_single_thread(uint8_t number_of_counters,
        uint32_t start,
        uint32_t multiplier)
{
    double c = 0;
    for (int i = 0; i < 1000000000; i++)
        c++;
    return c;
}
