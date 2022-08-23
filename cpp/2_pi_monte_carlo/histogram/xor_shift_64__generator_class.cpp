#include "xor_shift_64__generator_class.hpp"

unsigned long long XORShift64_Generator::next()
{
    x ^= (x >> 12);
    x ^= (x << 25);
    x ^= (x >> 27);

    x *= 2'685'821'657'736'338'717ULL;

    return x;
}
