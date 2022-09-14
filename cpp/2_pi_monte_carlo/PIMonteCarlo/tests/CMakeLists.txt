cmake_minimum_required(VERSION 3.12)

set(target_suffix "CPP_PROJECT_TEST")

set(project_name "PIMonteCarlo-Test")
set(target_project_name "${project_name}-${target_suffix}")

set(library_name "pmc")
set(target_library_name "${library_name}-${target_suffix}")

set(test_library_name "${library_name}-test")
set(target_test_library_name "${test_library_name}-${target_suffix}")

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

file(GLOB test_lib_inc CONFIGURE_DEPENDS ${lib_inc_dir}/tests/*.hpp)
file(GLOB test_lib_src CONFIGURE_DEPENDS ${lib_src_dir}/tests/*.cpp)

add_library(${target_test_library_name} ${test_lib_inc} ${test_lib_src})
set_target_properties(
    ${target_test_library_name}
    PROPERTIES
        OUTPUT_NAME ${test_library_name}
)

set(tests test.cpp)

add_executable(${target_project_name} ${tests})
set_target_properties(
    ${target_project_name}
    PROPERTIES
        OUTPUT_NAME ${project_name}
)

target_link_libraries(${target_project_name} ${target_test_library_name} ${target_library_name})
