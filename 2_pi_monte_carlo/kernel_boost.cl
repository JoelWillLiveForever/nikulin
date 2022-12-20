#pragma OPENCL C_LANGUAGE_VERSION 17

#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#pragma OPENCL EXTENSION cl_khr_int64_base_atomics : enable
#pragma OPENCL EXTENSION cl_khr_int64_extended_atomics : enable

typedef struct
{
    ulong good_points;
    ulong all_points;
} PIPoints;

typedef struct
{
    ulong seed;
    ulong current_value;
} RandomContext64;

typedef struct
{
    RandomContext64 context64;
    ulong bank[16];
    uint index;
} RandomContext1024;

typedef union
{
    double double_value;
    ulong integer_value;
} DoubleInteger;

typedef enum
{
    XOR_SHIFT_64,
    XOR_SHIFT_1024
} GeneratorType;

// XorShift64
void InitRandomContext64_WithSeed( RandomContext64 *context, ulong seed )
{
    context->seed = seed;
    context->current_value = seed;
}

ulong next_xs64( RandomContext64 *context )
{
    context->current_value ^= ( context->current_value >> 12 );
    context->current_value ^= ( context->current_value << 25 );
    context->current_value ^= ( context->current_value >> 27 );

    context->current_value *= 2685821657736338717ULL;

    return context->current_value;
}

double convert_to_double_64( RandomContext64 *context )
{
    DoubleInteger di;
    di.double_value = ( double )context->current_value;

    di.integer_value &= 0x3FFFFFFFFFFFFFF;
    di.integer_value |= 0x3C00000000000000;

    return di.double_value;
}

// XorShift1024
void InitRandomContext1024_WithSeed( RandomContext1024 *context1024, ulong seed )
{
    InitRandomContext64_WithSeed( &context1024->context64, seed );

    context1024->index = 0;

    for ( unsigned int i = 0; i < 16; i++ )
        context1024->bank[i] = next_xs64( &context1024->context64 );

    context1024->context64.current_value = seed;
}

ulong next_xs1024( RandomContext1024 *context )
{
    ulong num1 = context->bank[context->index];

    context->index++;
    context->index &= 15;

    ulong num2 = context->bank[context->index];

    num2 ^= ( num2 << 31 );
    num2 ^= ( num2 >> 11 );
    num1 ^= ( num1 >> 30 );

    context->bank[context->index] = num1 ^ num2;

    ulong ret = context->bank[context->index] * 1181783497276652981ULL;
    context->context64.current_value = ret;

    return ret;
}

double convert_to_double_xs1024( RandomContext1024 *context )
{
    DoubleInteger di;
    di.double_value = ( double )context->context64.current_value;

    di.integer_value &= 0x3FFFFFFFFFFFFFF;
    di.integer_value |= 0x3C00000000000000;

    return di.double_value;
}

__kernel void boost( __global PIPoints *pi_points_array, __global ulong *seeds, __global ulong *pi_points_array_indexes, __global GeneratorType *generator_type, __global int *error_code )
{
    int gid = get_global_id(0);

    RandomContext64 rctx64;
    InitRandomContext64_WithSeed(&rctx64, seeds[gid]);

    RandomContext1024 rctx1024;
    InitRandomContext1024_WithSeed(&rctx1024, seeds[gid]);

    ulong my_index = pi_points_array_indexes[gid];
    atom_inc(&pi_points_array[my_index].all_points);    // инкрементируем all_points

    barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);
    double x = 0, y = 0, len = 0;

    switch (*generator_type)
    {
        case XOR_SHIFT_64:
            next_xs64(&rctx64);
            x = convert_to_double_64(&rctx64);

            next_xs64(&rctx64);
            y = convert_to_double_64(&rctx64);
        break;
        case XOR_SHIFT_1024:
            next_xs1024(&rctx1024);
            x = convert_to_double_xs1024(&rctx1024);

            next_xs1024(&rctx1024);
            y = convert_to_double_xs1024(&rctx1024);
        break;
        default:
            *error_code = -1;
            return;
        break;
    }

    len = x*x + y*y;
    seeds[gid] = (len <= 1);

    // if (len <= 1)
    //     seeds[gid] = 1;

    barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);            // ждём пока все кернелы дойдут до этого места 
    atom_add(&pi_points_array[my_index].good_points, seeds[gid]);   // инкрементируем good_points

    barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);
    seeds[gid] = rctx1024.context64.current_value;  // здесь можно обойтись без switch case, так как нам нужно просто задать сид для будущих генераций

    *error_code = 0;
}

// don't work
/*
__kernel void boost( __global ulong *all_points, __global ulong *good_points, __global ulong *pi_numbers, __global ulong *pi_numbers_indexes,  __global uint *start, __global uint *multiplier, __global double *precision, __global double *pi, __global char *str, __global uint *number_of_counters)
{
    // Init
    int gid = get_global_id(0);

    RandomContext64 rctx;
    InitRandomContext64_WithSeed(&rctx, good_points[gid]);

    good_points[gid] = 0;

    // ulong my_index = gid;
    // my_index &= *number_of_counters;

    // barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);
    ulong my_index = pi_numbers_indexes[gid];
    pi_numbers[my_index] = 0;

    // Work
    // barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);
    ulong iterations = 1;
    *multiplier = 2;

    while (iterations < 3)
    {
        double x = 0, y = 0, len = 0;
        pi_numbers[my_index] = 0;

        for (ulong iter = 0; iter < iterations; iter++)
        {
            atom_inc(all_points);
            // barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);

            next_xs64(&rctx);
            x = convert_to_double_64(&rctx);

            next_xs64(&rctx);
            y = convert_to_double_64(&rctx);

            len = x*x + y*y;

            if (len <= 1)
                good_points[gid]++;

            // barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);
            atom_add(&pi_numbers[my_index], good_points[gid]);
        }

        // Get min and max values from pi_numbers
        // barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);

        ulong min_val = ULONG_MAX;
        ulong max_val = 0;

        for (int i = 0; i < *number_of_counters; i++)
        {
            min_val = min(pi_numbers[i], min_val);
            max_val = max(pi_numbers[i], max_val);
        }

        // ulong p = max_val - min_val;

        // barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);
        // if (p <= 100)
        // {
        //     double my_pi = 4.0 * p / (double)*all_points;
        //     *pi = my_pi;
        //     break;
        // }

        // iterations *= *multiplier;
        iterations++; = min_val;
        *multiplier = max_val;
    }
}
*/
