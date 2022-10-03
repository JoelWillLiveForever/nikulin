/* Условие задачи 2:
 * Вычислить значение числа Пи методом Монте-Карло с точностью 0.0001 */

#define ULONG_MAX 0xffffffffffffffffUL

unsigned long xs64_gen(unsigned long seed)
{
    seed ^= (seed >> 12);
    seed ^= (seed << 25);
    seed ^= (seed >> 27);

    return seed * ULONG_MAX;
}

__kernel void boost( __global const double *randoms, __global int *points )
{
    int i = get_global_id(0);
    points[i] = 0;

    unsigned long seed = randoms[i] * ULONG_MAX;
    
    seed = xs64_gen(seed);
    double x = (double) seed / (double) ULONG_MAX;
    
    seed = xs64_gen(seed);
    double y = (double) seed / (double) ULONG_MAX;

    double len = x*x + y*y;

    if (len <= 1)
        points[i] = 1;
}
