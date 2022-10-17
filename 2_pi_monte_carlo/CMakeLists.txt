cmake_minimum_required(VERSION 3.16)

project(
    PIMonteCarlo
    VERSION 1.1.0.0 
    LANGUAGES C CXX
)

# check, is it a subproject?
get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

# C17 & CPP20 use
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# define _CRT_SECURE_NO_WARNING
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

# search for required libraries (vcpkg)
set(Boost_NO_WARN_NEW_VERSIONS ON)
find_package(Boost 1.76.0 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIR})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

if (WIN32)
    find_path(GETOPT_INCLUDE_DIR getopt.h)
    include_directories(${GETOPT_INCLUDE_DIR})
    find_library(GETOPT_LIBRARY getopt)
    
    message("-- GETOPT_INCLUDE_DIR: ${GETOPT_INCLUDE_DIR}")
    message("-- GETOPT_LIBRARY: ${GETOPT_LIBRARY}")
endif()

#find_package(Cargs CONFIG REQUIRED)
#include_directories(${GETOPT_INCLUDE_PATH})
#find_library(GETOPT_LIBRARY getopt)

#find_package(CUDA)
#include_directories(${CUDA_INCLUDE_DIR})

# preprocessing version.h.in to version.h
string(TIMESTAMP TODAY "%d%m%Y")
configure_file(version.h.in version.h)
include_directories(${PROJECT_BINARY_DIR})

add_custom_target("${PROJECT_NAME}-PrecompiledHeaders" SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/pch.h
    ${CMAKE_CURRENT_SOURCE_DIR}/pch.hpp
)

# C:
add_library("${PROJECT_NAME}-generators" STATIC
    generators.h
    generators.c
)
set_target_properties(
    "${PROJECT_NAME}-generators"
    PROPERTIES
        OUTPUT_NAME "generators"
)

add_library("${PROJECT_NAME}-counters" STATIC
    counters.h
    counters.c
)
set_target_properties(
    "${PROJECT_NAME}-counters"
    PROPERTIES
        OUTPUT_NAME "counters"
)

add_executable("${PROJECT_NAME}-C" main.c)
target_link_libraries("${PROJECT_NAME}-C"
    PRIVATE 
    Threads::Threads
    PUBLIC
    ${OpenCL_LIBRARIES}
    ${GETOPT_LIBRARY}
    "${PROJECT_NAME}-counters"
    "${PROJECT_NAME}-generators"
)
target_precompile_headers("${PROJECT_NAME}-C" PUBLIC pch.h)

# copy kernel_boost.cl to .exe dir
add_custom_command(TARGET "${PROJECT_NAME}-C" POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/kernel_boost.cl
        $<TARGET_FILE_DIR:${PROJECT_NAME}-C>
)

# CPP:
add_library("${PROJECT_NAME}-classes" STATIC
    pi_monte_carlo_points_generator_class.hpp 
    pi_monte_carlo_points_generator_class.cpp
    true_pi_selector_class.hpp
    true_pi_selector_class.cpp
    pi_convergence_check_class.hpp
    pi_convergence_check_class.cpp
    samples.hpp
    samples.cpp
)
set_target_properties(
    "${PROJECT_NAME}-classes"
    PROPERTIES
        OUTPUT_NAME "classes"
)

add_executable("${PROJECT_NAME}-CPP" main.cpp)
target_link_libraries("${PROJECT_NAME}-CPP" PUBLIC
    ${Boost_LIBRARIES}
    "${PROJECT_NAME}-classes"
    "${PROJECT_NAME}-generators"
)
target_precompile_headers("${PROJECT_NAME}-CPP" PUBLIC pch.hpp)

# CPP TESTS:
add_library("${PROJECT_NAME}-tests" STATIC
    true_pi_selector_class_test.hpp
    true_pi_selector_class_test.cpp
)
set_target_properties(
    "${PROJECT_NAME}-tests"
    PROPERTIES
        OUTPUT_NAME "tests"
)

add_executable("${PROJECT_NAME}-CPP-TESTS" tests.cpp)
target_link_libraries("${PROJECT_NAME}-CPP-TESTS" PUBLIC 
    "${PROJECT_NAME}-tests"
    "${PROJECT_NAME}-classes"
)
target_precompile_headers("${PROJECT_NAME}-CPP-TESTS" PUBLIC pch.hpp)

# CUDA:
#add_executable("${PROJECT_NAME}-CUDA" cuda.cu)
#target_link_libraries("${PROJECT_NAME}-CUDA" PUBLIC ${CUDA_LIBRARIES})
