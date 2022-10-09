#ifndef __PRECOMPILED_HEADERS_H__
#define __PRECOMPILED_HEADERS_H__

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#include <sysinfoapi.h>

//#include <time.h>
//#include <io.h>
//#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#include <math.h>
#include <limits.h>

#include <stdbool.h>
#include <string.h>
#include <float.h>

#include <stdint.h>
#include <errno.h>

// vcpkg
#include <pthread.h>
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

#endif
