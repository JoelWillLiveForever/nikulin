cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

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
#find_package(GTest REQUIRED)
if (WIN32)
    find_package(Boost 1.76.0 COMPONENTS program_options REQUIRED)
    include_directories(${Boost_INCLUDE_DIR})

    find_package(OpenCL REQUIRED)
    include_directories(${OpenCL_INCLUDE_DIR})

    find_package(pthreads REQUIRED)
    include_directories(${pthreads_INCLUDE_DIR})

    find_path(getopt_INCLUDE_DIR getopt.h)
    include_directories(${getopt_INCLUDE_DIR})
    find_library(getopt_LIBRARIES getopt)
endif()

#find_package(CUDA)
#include_directories(${CUDA_INCLUDE_DIR})

# preprocessing version.h.in to version.h
string(TIMESTAMP TODAY "%d%m%Y")
configure_file(version.h.in version.h)
include_directories(${PROJECT_BINARY_DIR})

add_custom_target(PrecompiledHeaders SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/pch.h
    ${CMAKE_CURRENT_SOURCE_DIR}/pch.hpp
)

# C:
add_library(generators STATIC
    generators.h
    generators.c
)

add_library(counters STATIC
    counters.h
    counters.c
)

add_executable("${CMAKE_PROJECT_NAME}-C" main.c)
if (WIN32)
    target_link_libraries("${CMAKE_PROJECT_NAME}-C" PUBLIC
        ${pthreads_LIBRARIES}
        ${getopt_LIBRARIES}
        ${OpenCL_LIBRARIES}
        generators
        counters
    )
else()
    target_link_libraries("${CMAKE_PROJECT_NAME}-C" PUBLIC
        counters
        generators
        OpenCL
        pthread
    )
endif()
target_precompile_headers("${CMAKE_PROJECT_NAME}-C" PUBLIC pch.h)

# copy kernel_boost.cl to .exe dir
add_custom_command(TARGET "${CMAKE_PROJECT_NAME}-C" POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/kernel_boost.cl
        $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}-C>
)

# CPP:
add_library(classes STATIC
    pi_monte_carlo_points_generator_class.hpp 
    pi_monte_carlo_points_generator_class.cpp
    true_pi_selector_class.hpp
    true_pi_selector_class.cpp
    pi_convergence_check_class.hpp
    pi_convergence_check_class.cpp
    samples.hpp
    samples.cpp
)

add_executable("${CMAKE_PROJECT_NAME}-CPP" main.cpp)
if (WIN32)
    target_link_libraries("${CMAKE_PROJECT_NAME}-CPP" PUBLIC
        ${Boost_LIBRARIES}
        generators
        classes
    )
else()
    target_link_libraries("${CMAKE_PROJECT_NAME}-CPP" PUBLIC
        classes
        generators
        boost_program_options
    )
endif()
target_precompile_headers("${CMAKE_PROJECT_NAME}-CPP" PUBLIC pch.hpp)

# CPP TESTS:
add_library(tests STATIC
    true_pi_selector_class_test.hpp
    true_pi_selector_class_test.cpp
)

add_executable("${CMAKE_PROJECT_NAME}-CPP-TESTS" tests.cpp)
target_link_libraries("${CMAKE_PROJECT_NAME}-CPP-TESTS" PUBLIC 
    tests
    classes
)
target_precompile_headers("${CMAKE_PROJECT_NAME}-CPP-TESTS" PUBLIC pch.hpp)

# CUDA:
#add_executable("${CMAKE_PROJECT_NAME}-CUDA" cuda.cu)
#target_link_libraries("${CMAKE_PROJECT_NAME}-CUDA" PUBLIC ${CUDA_LIBRARIES})
