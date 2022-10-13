cmake_minimum_required(VERSION 3.16)

project(GlobalProject
    LANGUAGES C CXX
)

set(ALLOW_DUPLICATE_CUSTOM_TARGETS TRUE)

# C17 & CPP20 use
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# define _CRT_SECURE_NO_WARNING
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

add_subdirectory(1_weight_combinations)
add_subdirectory(2_pi_monte_carlo)
add_subdirectory(3_polygon_traversal_direction)