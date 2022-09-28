#ifndef __PRECOMPILED_HEADERS_H__
#define __PRECOMPILED_HEADERS_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#endif
