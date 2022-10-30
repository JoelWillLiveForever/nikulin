#ifndef __PRECOMPILED_HEADERS_H__
#define __PRECOMPILED_HEADERS_H__

#pragma warning(disable: 4193)	// warning из winbase.h
#pragma warning(disable: 5105)	// warning из cl_platform.h

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

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

#include <time.h>

#include <math.h>
#include <limits.h>

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <float.h>

#include <stdint.h>
#include <errno.h>

// vcpkg
#include <pthread.h>
#include <getopt.h>

// include OpenCL

//#define CL_TARGET_OPENCL_VERSION 120 !defined CL_TARGET_OPENCL_VERSION
#ifndef CL_TARGET_OPENCL_VERSION
#define CL_TARGET_OPENCL_VERSION 120
#endif

#if defined (__APPLE__) || defined (__MACOSX)
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

// user libraries
#include "generators/xor_shift.h"
#include "generators/xor_shift_thread_safe.h"

#endif
