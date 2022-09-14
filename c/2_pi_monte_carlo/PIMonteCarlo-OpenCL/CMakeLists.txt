cmake_minimum_required(VERSION 3.12)

# суффикс для целей в текущем CMakeLists.txt
set(target_suffix "C_PROJECT")

# имя проекта (и бинарника)
set(project_name "PIMonteCarlo-OpenCL")
set(target_project_name "${project_name}-${target_suffix}") # с суффиксом

# проект, версия и ЯП
project(
    ${project_name}
    VERSION 1.0.0.0
    LANGUAGES C
)

# path to main file
set(app main.c)

# получаем бинарник с именем OUTPUT_NAME
add_executable(${target_project_name} ${app})
set_target_properties(
    ${target_project_name}
    PROPERTIES
        OUTPUT_NAME ${project_name}
)

# слинковать библиотеку и бинарник
target_link_libraries(${target_project_name} -lOpenCL)

# скопировать исходники kernel (OpenCL) в папку с бинарником во время вызова cmake
configure_file(kernel_boost.cl kernel_boost.cl COPYONLY)
