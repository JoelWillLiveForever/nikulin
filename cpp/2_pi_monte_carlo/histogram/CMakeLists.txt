cmake_minimum_required(VERSION 3.12)


set(target_suffix "JUPITER_NOTEBOOK")

set(project_name "ResearchGenerators")
set(target_project_name "${project_name}-${target_suffix}") # с суффиксом

project(
    ${project_name}
    VERSION 1.0.0.0
    LANGUAGES CXX
)


# libs
set(generators_library_name "generators")
set(target_generators_library_name "${generators_library_name}-${target_suffix}") # с суффиксом

set(samples_library_name "samples")
set(target_samples_library_name "${samples_library_name}-${target_suffix}") # с суффиксом

set(lib_general_inc
    pch.hpp
)

set(generators_lib_inc
    ${lib_general_inc}
    xor_shift_64__generator_class.hpp
    xor_shift_1024__generator_class.hpp
)
set(generators_lib_src
    xor_shift_64__generator_class.cpp
    xor_shift_1024__generator_class.cpp
)

add_library(${target_generators_library_name} ${generators_lib_inc} ${generators_lib_src})
set_target_properties(
    ${target_generators_library_name}
    PROPERTIES
        OUTPUT_NAME ${generators_library_name}
)


set(samples_lib_inc
    ${lib_general_inc}
    random_generator__sample_abstract_class.hpp
    mt19937__sample_class.hpp
    xor_shift_64__sample_class.hpp
    xor_shift_1024__sample_class.hpp
)
set(samples_lib_src
    mt19937__sample_class.cpp
    xor_shift_64__sample_class.cpp
    xor_shift_1024__sample_class.cpp
)

add_library(${target_samples_library_name} ${samples_lib_inc} ${samples_lib_src})
set_target_properties(
    ${target_samples_library_name}
    PROPERTIES
        OUTPUT_NAME ${samples_library_name}
)


# executable
set(app main.cpp)
add_executable(${target_project_name} ${app})
set_target_properties(
    ${target_project_name}
    PROPERTIES
        OUTPUT_NAME ${project_name}
)


target_link_libraries(${target_project_name} 
    ${target_samples_library_name}
    ${target_generators_library_name} 
)
configure_file(research_generators.ipynb research_generators.ipynb COPYONLY)
