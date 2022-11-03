#ifndef __COUNTERS_H__
#define __COUNTERS_H__

double get_pi_single_thread(long number_of_counters, 
        uint32_t start, 
        uint32_t multiplier,
        double eps,
        bool use_xs1024);

double get_pi_multithread(long number_of_counters, 
        unsigned start, 
        unsigned multiplier,
        double eps, 
        unsigned number_of_processors,
        bool use_xs1024);

double get_pi_opencl(long number_of_counters,
        uint32_t start,
        uint32_t multiplier,
        double eps,
        bool use_xs1024);

#endif
