#include <limits.h>
#define XOR_SHIFT_RAND_MAX ULONG_MAX;

// генератор случайных чисел по алгоритму XorShift64
unsigned long xor_shift_64(unsigned long x);

void seed_64(unsigned long seed);
unsigned long next_64();

// генератор случайных чисел по алгоритму XorShift1024
unsigned long xor_shift_1024();

void seed_1024(unsigned long seed);
unsigned long next_1024();
