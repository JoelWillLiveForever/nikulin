#ifndef __PRECOMPILED_HEADERS_H__
#define __PRECOMPILED_HEADERS_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <limits.h>

#include <stdbool.h>
#include <string.h>
#include <float.h>

#include <stdint.h>
#include <errno.h>

#include <pthread.h>
#include <unistd.h>

#include <getopt.h>

// include OpenCL

#ifndef CL_TARGET_OPENCL_VERSION
#define CL_TARGET_OPENCL_VERSION 120
#endif

#if defined (__APPLE__) || defined (__MACOSX)
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

// user libraries
#include "generators.h"
#include "counters.h"

#endif
