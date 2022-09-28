#ifndef __COUNTERS_H__
#define __COUNTERS_H__

#include "pch.h"

double get_pi_single_thread(uint8_t number_of_counters, 
        uint32_t start, 
        uint32_t multiplier);

//double get_pi_multithread(uint8_t number_of_counters, 
//        uint32_t start, 
//        uint32_t multiplier, 
//        uint8_t  amount_of_processors);
//
//double get_pi_opencl(uint8_t number_of_counters,
//        uint32_t start,
//        uint32_t multiplier);
//
//double get_pi_cpu_with_gpu(uint8_t number_of_counters,
//        uint32_t start,
//        uint32_t multiplier,
//        uint8_t  amount_of_processors);

#endif
