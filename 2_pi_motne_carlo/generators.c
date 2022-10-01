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

    uint64_t gen = (is_xs1024) ? xs1024_gen() : xs64_gen();

    return ((double) gen) / ((double) ULLONG_MAX);
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

// потоко-безопасные реализации

uint64_t xs64_gen_thread_safe(uint64_t *pointer_to_xs64_value)
{
    (*pointer_to_xs64_value) ^= ( (*pointer_to_xs64_value) >> 12);
    (*pointer_to_xs64_value) ^= ( (*pointer_to_xs64_value) << 25);
    (*pointer_to_xs64_value) ^= ( (*pointer_to_xs64_value) >> 27);

    (*pointer_to_xs64_value) *= 2685821657736338717ULL;

    return (*pointer_to_xs64_value);
}

uint64_t xs1024_gen_thread_safe(uint64_t *pointer_to_bank_numbers, uint32_t *pointer_to_bank_index)
{
    uint64_t num1 = pointer_to_bank_numbers[(*pointer_to_bank_index)];

    (*pointer_to_bank_index)++;
    (*pointer_to_bank_index) &= 15;

    uint64_t num2 = pointer_to_bank_numbers[(*pointer_to_bank_index)];

    num2 ^= (num2 << 31);
    num2 ^= (num2 >> 11);
    num1 ^= (num1 >> 30);

    pointer_to_bank_numbers[(*pointer_to_bank_index)] = num1 ^ num2;

    return pointer_to_bank_numbers[(*pointer_to_bank_index)] * 1181783497276652981ULL;
}

double next_thread_safe(uint64_t seed, uint8_t is_xs1024, uint64_t *xor_shift_64_value, uint64_t *xor_shift_1024_bank_numbers, uint32_t *xor_shift_1024_bank_index)
{
    if ( seed )
    {
        (*xor_shift_64_value) = seed;

        if (is_xs1024)
        {
            for ((*xor_shift_1024_bank_index) = 0; (*xor_shift_1024_bank_index) < 16; (*xor_shift_1024_bank_index)++)
                xor_shift_1024_bank_numbers[(*xor_shift_1024_bank_index)] = xs64_gen_thread_safe( xor_shift_64_value );
            (*xor_shift_1024_bank_index) = 0;
        }
    }
    else if ( !(*xor_shift_64_value) )
    {
        (*xor_shift_64_value) = time(NULL);

        if (is_xs1024)
        {
            for ((*xor_shift_1024_bank_index) = 0; (*xor_shift_1024_bank_index) < 16; (*xor_shift_1024_bank_index)++)
                xor_shift_1024_bank_numbers[(*xor_shift_1024_bank_index)] = xs64_gen_thread_safe( xor_shift_64_value );
            (*xor_shift_1024_bank_index) = 0;
        }
    }

    uint64_t gen = (is_xs1024) 
        ? xs1024_gen_thread_safe( xor_shift_1024_bank_numbers, xor_shift_1024_bank_index )
        : xs64_gen_thread_safe( xor_shift_64_value );

    return ((double) gen) / ((double) ULLONG_MAX);
}
