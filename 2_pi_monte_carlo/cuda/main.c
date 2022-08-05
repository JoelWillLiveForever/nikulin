#include <time.h>
#include <stdio.h>
#include <limits.h>
#include "xor_shift.h"

int main()
{
    seed_1024((unsigned long) time(NULL));

    for (unsigned long i = 1; i < ULONG_MAX; i++)
        printf("Value: %32lu;\n", next_1024());

    return 0;
}
