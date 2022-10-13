cmake_minimum_required(VERSION 3.16)

project(
    PolygonTraversalDirection
    VERSION 1.1.0.0 
    LANGUAGES C CXX
)

# C17 & CPP20 use
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# define _CRT_SECURE_NO_WARNING
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

add_custom_target("${PROJECT_NAME}-PrecompiledHeaders" SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/pch.hpp
)

# C:
add_library("${PROJECT_NAME}-foo" STATIC
    foo.h
    cross_product.c
    polygon_traversal_direction.c
)
set_target_properties(
    "${PROJECT_NAME}-foo"
    PROPERTIES
        OUTPUT_NAME "foo"
)

add_executable("${PROJECT_NAME}-C" main.c)
target_link_libraries("${PROJECT_NAME}-C" PUBLIC
    "${PROJECT_NAME}-foo"
)

# CPP:
add_library("${PROJECT_NAME}-classes" STATIC
    point_class.hpp
    point_class.cpp
    cross_product_class.hpp
    cross_product_class.cpp
    direction_finder_class.hpp
    direction_finder_class.cpp
)
set_target_properties(
    "${PROJECT_NAME}-classes"
    PROPERTIES
        OUTPUT_NAME "classes"
)

add_executable("${PROJECT_NAME}-CPP" main.cpp)
target_link_libraries("${PROJECT_NAME}-CPP" PUBLIC
    "${PROJECT_NAME}-classes"
)
target_precompile_headers("${PROJECT_NAME}-CPP" PUBLIC pch.hpp)

# copy source.txt to .exe dir
add_custom_command(TARGET "${PROJECT_NAME}-CPP" POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/source.txt
        $<TARGET_FILE_DIR:${PROJECT_NAME}-CPP>
)

add_library("${PROJECT_NAME}-tests" STATIC
    cross_product_class_test.hpp
    cross_product_class_test.cpp
    direction_finder_class_test.hpp
    direction_finder_class_test.cpp
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