#ifndef __COUNTERS_H__
#define __COUNTERS_H__

typedef enum
{
    // Порядок имеет значение, используется в OpenCL
    XOR_SHIFT_64,
    XOR_SHIFT_1024,

    // Могут быть в любом порядке
    XOR_SHIFT_16,
    XOR_SHIFT_32,
    RAND16,
    RAND32,
    RAND64
} GeneratorType;    // check error

double get_pi_single_thread( uint32_t number_of_counters,
                             uint32_t start,
                             uint32_t multiplier,
                             double eps,
                             GeneratorType generator_type );

double get_pi_multithread( uint32_t number_of_counters,
                           uint32_t start,
                           uint32_t multiplier,
                           double eps,
                           long number_of_processors,
                           GeneratorType generator_type );

double get_pi_opencl( uint32_t number_of_counters,
                      uint64_t start,
                      uint32_t multiplier,
                      double eps,
                      GeneratorType generator_type );

#endif
