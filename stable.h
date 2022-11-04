#pragma once

#ifdef _MSC_VER
	__pragma(warning(disable: 4005 4193 4244 4668))
#endif

// generators library
#include "random/src/xor_shift.h"
#include "random/src/xor_shift_thread_safe.h"

#ifdef __cplusplus
	#include <iostream>
	#include <fstream>
	#include <iomanip>
	#include <sstream>
	#include <random>
	#include <thread>
	#include <vector>
	#include <cfloat>
	#include <cmath>
	#include <stdlib.h>
	#include <chrono>
	#include <random>
	#include <climits>
	#include <string>
	#include <algorithm>
	#include <stdexcept>
	#include <iterator>
	#include <strstream>

	#include <boost/program_options.hpp>
	#include <boost/program_options/errors.hpp>
	#include <boost/filesystem.hpp>

	#include <spdlog/spdlog.h>
	#include <spdlog/sinks/basic_file_sink.h>
	#include <spdlog/sinks/rotating_file_sink.h>
	#include <spdlog/fmt/ranges.h>
	#include <spdlog/sinks/stdout_color_sinks.h>

	//#include <spdlog/fmt/ostr.h
#endif

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#ifdef _WIN32
	#include <windows.h>
	#include <sysinfoapi.h>
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
#ifndef CL_TARGET_OPENCL_VERSION
	#define CL_TARGET_OPENCL_VERSION 120
#endif

#if defined (__APPLE__) || defined (__MACH__)
	#include <OpenCL/opencl.h>
#else
	#include <CL/cl.h>
#endif
