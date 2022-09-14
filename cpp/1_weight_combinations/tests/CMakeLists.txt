cmake_minimum_required(VERSION 3.12)

set(target_suffix "CPP_PROJECT_TEST")

set(project_name "WeightCombinations-Test")
set(target_project_name "${project_name}-${target_suffix}")

set(library_name "wc")
set(target_library_name "${library_name}-${target_suffix}")

project(
    ${project_name}
    VERSION 1.0.0.0
    LANGUAGES CXX
)

set(lib_inc_dir ../include)
set(lib_src_dir ../src)

file(GLOB lib_inc CONFIGURE_DEPENDS ${lib_inc_dir}/*.hpp)
file(GLOB lib_src CONFIGURE_DEPENDS ${lib_src_dir}/*.cpp)

add_library(${target_library_name} ${lib_inc} ${lib_src})
set_target_properties(
    ${target_library_name}
    PROPERTIES
        OUTPUT_NAME ${library_name}
)

set(tests test.cpp)

add_executable(${target_project_name} ${tests})
set_target_properties(
    ${target_project_name}
    PROPERTIES
        OUTPUT_NAME ${project_name}
)

target_link_libraries(${target_project_name} ${target_library_name})
