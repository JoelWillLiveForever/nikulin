#include "generators.h"

uint64_t current_xs64_value;
uint64_t xs64_gen()
{
    current_xs64_value ^= (current_xs64_value >> 12);
    current_xs64_value ^= (current_xs64_value << 25);
    current_xs64_value ^= (current_xs64_value >> 27);

    current_xs64_value *= 2685821657736338717ULL;

    return current_xs64_value;
}

uint64_t bank_numbers[16]; 
uint32_t bank_index = 0;
uint64_t xs1024_gen()
{
    uint64_t num1 = bank_numbers[bank_index];

    bank_index++;
    bank_index &= 15;

    uint64_t num2 = bank_numbers[bank_index];

    num2 ^= (num2 << 31);
    num2 ^= (num2 >> 11);
    num1 ^= (num1 >> 30);

    bank_numbers[bank_index] = num1 ^ num2;

    return bank_numbers[bank_index] * 1181783497276652981ULL;
}

double next(uint64_t seed, uint8_t is_xs1024)
{
    if (seed)
    {
        current_xs64_value = seed;
        if (is_xs1024)
        {
            for (bank_index = 0; bank_index < 16; bank_index++)
                bank_numbers[bank_index] = xs64_gen();
            bank_index = 0;
        }
    }
    else if (!current_xs64_value)
    {
        current_xs64_value = time(NULL);
        if (is_xs1024)
        {
            for (bank_index = 0; bank_index < 16; bank_index++)
                bank_numbers[bank_index] = xs64_gen();
            bank_index = 0;
        }
    }

    uint64_t gen;
    if (is_xs1024)
        gen = xs1024_gen();
    else
        gen = xs64_gen();

    return ((double) gen) / ((double) ULLONG_MAX);
}
