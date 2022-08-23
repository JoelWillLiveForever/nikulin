cmake_minimum_required(VERSION 3.10)    # минимально-допустимая версия CMake

# проект, его версия, описание и ЯП
project(PIMonteCarlo
    VERSION 1.0.0
    DESCRIPTION "Simple app for find a PI number with required accuracy"
    LANGUAGES CXX)          

set(SRC_DIR src)
set(SRC_EXE ${SRC_DIR}/main.cpp)     # список исходников для бинарника

# список исходников для библиотеки
set(SRC_LIB ${SRC_DIR}/pi_convergence_check_class.cpp 
    ${SRC_DIR}/true_pi_selector_class.cpp
    ${SRC_DIR}/pi_monte_carlo_points_generator_class.cpp)

add_library(foo STATIC ${SRC_LIB})   # создание статической библиотеки с именем foo
add_executable(binary ${SRC_EXE})    # создание бинарника

target_link_libraries(binary foo) # линковка программы с библиотекой
