#ifndef __COUNTERS_H__
#define __COUNTERS_H__

#include "pch.h"

double get_pi_single_thread(uint8_t number_of_counters, 
        uint32_t start, 
        uint32_t multiplier,
        double eps,
        bool use_xs1024);

double get_pi_multithread(unsigned number_of_counters, 
        unsigned start, 
        unsigned multiplier,
        double eps, 
        unsigned number_of_processors,
        bool use_xs1024);

//double get_pi_opencl(uint8_t number_of_counters,
//        uint32_t start,
//        uint32_t multiplier,
//        double eps);
//
//double get_pi_cpu_with_gpu(uint8_t number_of_counters,
//        uint32_t start,
//        uint32_t multiplier,
//        double eps,
//        uint8_t  amount_of_processors);

#endif
