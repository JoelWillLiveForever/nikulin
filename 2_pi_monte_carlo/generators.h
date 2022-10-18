#ifndef __GENERATORS_H__
#define __GENERATORS_H__

#if 1
#include "../pch.h"
#else
#include <stdint.h>
#include <limits.h>
#include <time.h>
#endif

double next(uint64_t seed, uint8_t is_xs1024);
double next_thread_safe(uint64_t seed, uint8_t is_xs1024, uint64_t *xs64_value, uint64_t *xs1024_bank_numbers, uint32_t *xs1024_bank_index);

#endif
