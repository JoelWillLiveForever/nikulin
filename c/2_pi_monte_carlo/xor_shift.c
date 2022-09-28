#include "../include/xor_shift.h"

static unsigned long prev_64;
unsigned long xor_shift_64(unsigned long x)
{
    if (x == 0) return 0;

    x ^= (x >> 12);
    x ^= (x << 25);
    x ^= (x >> 27);

    return x * 2685821657736338717UL;
}

void seed_64(unsigned long seed)
{
    prev_64 = seed;
}

unsigned long next_64()
{
    prev_64 = xor_shift_64(prev_64);
    return prev_64;
}

static unsigned long S[16], s0, s1;
static unsigned char p;

unsigned long xor_shift_1024()
{
    s0 = S[p];
    p = (p + 1) & 15;
    s1 = S[p];

    s1 ^= (s1 << 31);
    s1 ^= (s1 >> 11);
    s0 ^= (s0 >> 30);

    S[p] = s0 ^ s1;
    return S[p] * 1181783497276652981UL;
}

void seed_1024(unsigned long seed)
{
    seed_64(seed);
    S[0] = next_64();

    for (p = 1; p < 16; p++)
        S[p] = next_64();

    p = 0;
}

unsigned long next_1024()
{
    return xor_shift_1024();
}
