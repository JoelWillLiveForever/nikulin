#pragma once

//#ifdef _MSC_VER
//#pragma warning(push)
//#pragma warning(disable: 4005)
//#pragma warning(disable: 193)
//#pragma warning(disable: 4244)
//#pragma warning(disable: 4668)
//#endif

#ifdef __cplusplus
    #include <filesystem>
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

    #include <boost/program_options.hpp>
    #include <boost/program_options/errors.hpp>
    #include <boost/filesystem.hpp>

    #ifdef __GNUC__
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    #endif
    #include <strstream>
    #ifdef __GNUC__
        #pragma GCC diagnostic pop
    #endif

    #include <spdlog/spdlog.h>
    //    #include <spdlog/sinks/basic_file_sink.h>
    #include <spdlog/sinks/rotating_file_sink.h>
    #include <spdlog/fmt/ranges.h>
    #include <spdlog/sinks/stdout_color_sinks.h>

    //#include <spdlog/fmt/ostr.h
#endif

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#ifdef _WIN32
    #ifdef __cplusplus
        #include <WinSock2.h>
    #else
        #include <windows.h>
    #endif
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
    #define CL_TARGET_OPENCL_VERSION 220
#endif

#if defined (__APPLE__) || defined (__MACH__)
    #include <OpenCL/opencl.h>
#else
    #ifdef _MSC_VER
        #pragma warning(disable: 4193)
        #include <CL/cl.h>
    #else
        #include <CL/cl.h>
    #endif
#endif

// random library
// #ifdef _MSC_VER
//     #pragma warning(push)
//     #pragma warning(disable: 4651)
// #endif

#ifdef __cplusplus
extern "C"
{
#include <random/context.h>
#include <random/rand.h>
#include <random/xor_shift.h>
#include <random/converter.h>
#include <random/buffer_placeholder.h>
}
#else
#include <random/context.h>
#include <random/rand.h>
#include <random/xor_shift.h>
#include <random/converter.h>
#include <random/buffer_placeholder.h>
#endif

// #ifdef _MSC_VER
//     #pragma warning(pop)
// #endif

