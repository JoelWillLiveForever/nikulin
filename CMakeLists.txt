cmake_minimum_required(VERSION 3.16)

project(NikulinTasks
    VERSION 1.2.0.0
    LANGUAGES C CXX
)

# C17 & CPP20 use
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# define _CRT_SECURE_NO_WARNING
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

# all warnings as errors
# https://stackoverflow.com/questions/2368811/how-to-set-warning-level-in-cmake
# https://cmake.org/cmake/help/latest/command/add_compile_options.html
if (MSVC)
   # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
   # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

# option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# search and load required libraries
set(Boost_NO_WARN_NEW_VERSIONS ON)
find_package(Boost 1.76.0 COMPONENTS program_options filesystem REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIR})

# если венда, то используются библиотеки из vcpkg, 
# под linux pthread.h и getopt.h встроены в систему и не нужнаются в подгрузке из vcpkg
if (WIN32)
    find_package(PThreads4W REQUIRED)
    include_directories(${PThreads4W_INCLUDE_DIR})

    find_path(GETOPT_INCLUDE_DIR getopt.h)
    include_directories(${GETOPT_INCLUDE_DIR})
    find_library(GETOPT_LIBRARY getopt)
    
    message("-- GETOPT_INCLUDE_DIR: ${GETOPT_INCLUDE_DIR}")
    message("-- GETOPT_LIBRARY: ${GETOPT_LIBRARY}")
endif()

find_package(GTest CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
#find_package(fmt CONFIG REQUIRED)

# Get the current working branch
execute_process(
    #COMMAND git log -1 --format=%h
    
    COMMAND git rev-parse HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
message("-- GIT_COMMIT_HASH: ${GIT_COMMIT_HASH}")

# Get current date
string(TIMESTAMP TODAY "%d%m%Y")

# preprocessing version.h.in to version.h
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/version.h.in 
    ${CMAKE_CURRENT_BINARY_DIR}/version.h
)
include_directories(${PROJECT_BINARY_DIR})

add_custom_target(PrecompiledHeaders SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/pch.h
    ${CMAKE_CURRENT_SOURCE_DIR}/pch.hpp
)

# add libraries
add_library(generators STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/xor_shift.h
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/xor_shift.c
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/xor_shift_thread_safe.h
    ${CMAKE_CURRENT_SOURCE_DIR}/generators/xor_shift_thread_safe.c
)

add_library(modules STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/2_pi_monte_carlo/counters.h
    ${CMAKE_CURRENT_SOURCE_DIR}/2_pi_monte_carlo/counters.c

    ${CMAKE_CURRENT_SOURCE_DIR}/3_polygon_traversal_direction/foo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/3_polygon_traversal_direction/cross_product.c
    ${CMAKE_CURRENT_SOURCE_DIR}/3_polygon_traversal_direction/polygon_traversal_direction.c
)

add_library(classes STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/1_weight_combinations/weight_combinator.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/1_weight_combinations/weight_combinator.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/1_weight_combinations/weight_combinator_io.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/1_weight_combinations/weight_combinator_io.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/2_pi_monte_carlo/pi_monte_carlo_points_generator_class.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/2_pi_monte_carlo/pi_monte_carlo_points_generator_class.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/2_pi_monte_carlo/true_pi_selector_class.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/2_pi_monte_carlo/true_pi_selector_class.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/2_pi_monte_carlo/pi_convergence_check_class.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/2_pi_monte_carlo/pi_convergence_check_class.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/2_pi_monte_carlo/samples.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/2_pi_monte_carlo/samples.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/3_polygon_traversal_direction/point_class.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/3_polygon_traversal_direction/point_class.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/3_polygon_traversal_direction/cross_product_class.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/3_polygon_traversal_direction/cross_product_class.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/3_polygon_traversal_direction/direction_finder_class.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/3_polygon_traversal_direction/direction_finder_class.cpp
)

# add_library(tests STATIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/1_weight_combinations/weight_combinator_class_test.hpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/1_weight_combinations/weight_combinator_class_test.cpp

#     ${CMAKE_CURRENT_SOURCE_DIR}/2_pi_monte_carlo/true_pi_selector_class_test.hpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/2_pi_monte_carlo/true_pi_selector_class_test.cpp

#     ${CMAKE_CURRENT_SOURCE_DIR}/3_polygon_traversal_direction/cross_product_class_test.hpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/3_polygon_traversal_direction/cross_product_class_test.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/3_polygon_traversal_direction/direction_finder_class_test.hpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/3_polygon_traversal_direction/direction_finder_class_test.cpp
# )

# add executables
# Weight Combinations
add_executable(WeightCombinations-C
    ${CMAKE_CURRENT_SOURCE_DIR}/1_weight_combinations/weight_combinations.c
)
target_precompile_headers(WeightCombinations-C PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/pch.h
)

add_executable(WeightCombinations-C-DETAILED
    ${CMAKE_CURRENT_SOURCE_DIR}/1_weight_combinations/weight_combinations_detail.c
)
target_precompile_headers(WeightCombinations-C-DETAILED REUSE_FROM WeightCombinations-C)

add_executable(WeightCombinations-CPP
    ${CMAKE_CURRENT_SOURCE_DIR}/1_weight_combinations/main.cpp
)
target_link_libraries(WeightCombinations-CPP PUBLIC
    classes
    #${GETOPT_LIBRARY}   # empty if build in linux
    spdlog::spdlog
    spdlog::spdlog_header_only
    Boost::program_options
    Boost::filesystem
)
target_precompile_headers(WeightCombinations-CPP PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/pch.hpp
)
add_custom_command(TARGET WeightCombinations-CPP POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/1_weight_combinations/source.txt
        $<TARGET_FILE_DIR:WeightCombinations-CPP>/source_weight_combinations.txt
)

add_executable(WeightCombinations-CPP-TESTS
    ${CMAKE_CURRENT_SOURCE_DIR}/1_weight_combinations/tests.cpp
)
target_link_libraries(WeightCombinations-CPP-TESTS PUBLIC
    # tests
    classes
    GTest::gmock
    GTest::gtest 
    GTest::gmock_main
    GTest::gtest_main
)
target_precompile_headers(WeightCombinations-CPP-TESTS REUSE_FROM WeightCombinations-CPP)

# PI Monte Carlo
add_executable(PIMonteCarlo-C 
    ${CMAKE_CURRENT_SOURCE_DIR}/2_pi_monte_carlo/main.c
)
target_link_libraries(PIMonteCarlo-C PUBLIC
    modules
    generators
    ${GETOPT_LIBRARY}           # empty if build in linux
    ${OpenCL_LIBRARIES}
    ${PThreads4W_LIBRARIES}     # empty if build in linux
)
target_precompile_headers(PIMonteCarlo-C REUSE_FROM WeightCombinations-C)
#target_compile_options(PIMonteCarlo-C PRIVATE
#    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
#        -Wall -Wextra -Wpedantic -Werror>
#    $<$<CXX_COMPILER_ID:MSVC>:
#        /W4 /WX>
#)

# Disabled
#add_executable(PIMonteCarlo-CPP
#    ${CMAKE_CURRENT_SOURCE_DIR}/2_pi_monte_carlo/main.cpp
#)
#target_link_libraries(PIMonteCarlo-CPP PUBLIC
#    classes
#    generators
#    spdlog::spdlog
#    spdlog::spdlog_header_only
#    Boost::program_options
#)
#target_precompile_headers(PIMonteCarlo-CPP REUSE_FROM WeightCombinations-CPP)

# add_executable(PIMonteCarlo-CPP-TESTS
#     ${CMAKE_CURRENT_SOURCE_DIR}/2_pi_monte_carlo/tests.cpp
# )
# target_link_libraries(PIMonteCarlo-CPP-TESTS PUBLIC
#     tests
#     classes
# )
# target_precompile_headers(PIMonteCarlo-CPP-TESTS REUSE_FROM WeightCombinations-CPP)

# Polygon Traversal Direction
add_executable(PolygonTraversalDirection-C
    ${CMAKE_CURRENT_SOURCE_DIR}/3_polygon_traversal_direction/main.c
)
target_link_libraries(PolygonTraversalDirection-C PUBLIC
    modules
)
target_precompile_headers(PolygonTraversalDirection-C REUSE_FROM WeightCombinations-C)

# Disabled
#add_executable(PolygonTraversalDirection-CPP
#    ${CMAKE_CURRENT_SOURCE_DIR}/3_polygon_traversal_direction/main.cpp
#)
#target_link_libraries(PolygonTraversalDirection-CPP PUBLIC
#    classes
#)
#target_precompile_headers(PolygonTraversalDirection-CPP REUSE_FROM WeightCombinations-CPP)
#add_custom_command(TARGET PolygonTraversalDirection-CPP POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        ${CMAKE_CURRENT_SOURCE_DIR}/3_polygon_traversal_direction/source.txt
#        $<TARGET_FILE_DIR:PolygonTraversalDirection-CPP>/source_polygon_traversal_direction.txt
#)

# add_executable(PolygonTraversalDirection-CPP-TESTS
#     ${CMAKE_CURRENT_SOURCE_DIR}/3_polygon_traversal_direction/tests.cpp
# )
# target_link_libraries(PolygonTraversalDirection-CPP-TESTS PUBLIC
#     tests
#     classes
# )
# target_precompile_headers(PolygonTraversalDirection-CPP-TESTS REUSE_FROM WeightCombinations-CPP)