cmake_minimum_required(VERSION 3.12)

set(target_suffix "CPP_C_PI_MONTE_CARLO")

set(project_name "PIMonteCarlo")
set(target_project_name "${project_name}-${target_suffix}")

project(
    ${project_name}
    VERSION 1.0.0.0
    LANGUAGES C CXX
)

# CPP LIBS
set(cpp_library_name "pimc_cpp")
set(target_cpp_library_name "${cpp_library_name}-${target_suffix}")

set(cpp_test_library_name "${cpp_library_name}-test")
set(target_cpp_test_library_name "${cpp_test_library_name}-${target_suffix}")

# C LIBS
set(c_library_name "pimc_c")
set(target_c_library_name "${c_library_name}-${target_suffix}")

# CPP LIBRARY
file(GLOB cpp_inc CONFIGURE_DEPENDS 
    pch.hpp
    generators.h 
    samples.hpp 
    pi_convergence_check_class.hpp 
    pi_monte_carlo_points_generator_class.hpp
    true_pi_selector_class.hpp )

file(GLOB cpp_src CONFIGURE_DEPENDS
    samples.cpp
    generators.c
    pi_convergence_check_class.cpp
    pi_monte_carlo_points_generator_class.cpp
    true_pi_selector_class.cpp)

add_library(${target_cpp_library_name} ${cpp_inc} ${cpp_src})
set_target_properties(
    ${target_cpp_library_name}
    PROPERTIES
        OUTPUT_NAME ${cpp_library_name}
)

# CPP TEST LIBRARY
file(GLOB cpp_test_inc CONFIGURE_DEPENDS 
    pch.hpp
    true_pi_selector_class_test.hpp)

file(GLOB cpp_test_src CONFIGURE_DEPENDS
    true_pi_selector_class_test.cpp)

add_library(${target_cpp_test_library_name} ${cpp_test_inc} ${cpp_test_src})
set_target_properties(
    ${target_cpp_test_library_name}
    PROPERTIES
        OUTPUT_NAME ${cpp_test_library_name}
)

# C LIBRARY
file(GLOB c_inc CONFIGURE_DEPENDS
    pch.h
    generators.h
    counters.h)

file(GLOB c_src CONFIGURE_DEPENDS
    generators.c
    counters.c)

add_library(${target_c_library_name} ${c_inc} ${c_src})
set_target_properties(
    ${target_c_library_name}
    PROPERTIES
        OUTPUT_NAME ${c_library_name}
)

# MAIN.CPP
add_executable("${target_project_name}-CPP" main.cpp)
set_target_properties(
    "${target_project_name}-CPP"
    PROPERTIES
        OUTPUT_NAME "${project_name}-CPP"
)

find_package( Boost 1.76.0 COMPONENTS program_options REQUIRED )
target_include_directories( "${target_project_name}-CPP" PRIVATE ${Boost_INCLUDE_DIR} )

target_link_libraries("${target_project_name}-CPP" ${Boost_LIBRARIES} ${target_cpp_library_name})

# TEST.CPP
add_executable("${target_project_name}-CPP-TEST" test.cpp)
set_target_properties(
    "${target_project_name}-CPP-TEST"
    PROPERTIES
        OUTPUT_NAME "${project_name}-CPP-TEST"
)
target_link_libraries("${target_project_name}-CPP-TEST" ${target_cpp_test_library_name} ${target_cpp_library_name})

# MAIN.C
add_executable("${target_project_name}-C" main.c)
set_target_properties(
    "${target_project_name}-C"
    PROPERTIES
        OUTPUT_NAME "${project_name}-C"
)

find_package( OpenCL REQUIRED )
target_include_directories( "${target_project_name}-C" PRIVATE ${OpenCL_INCLUDE_DIR} )

target_link_libraries("${target_project_name}-C" ${OpenCL_LIBRARIES} ${target_c_library_name})

configure_file(kernel_boost.cl kernel_boost.cl COPYONLY)
