cmake_minimum_required(VERSION 3.12)

# суффикс для целей в текущем CMakeLists.txt
set(target_suffix "CPP_PROJECT")

# имя проекта (и бинарника)
set(project_name "PIMonteCarlo")
set(target_project_name "${project_name}-${target_suffix}") # с суффиксом

# имя библиотеки
set(library_name "pmc")
set(target_library_name "${library_name}-${target_suffix}") # с суффиксом

# проект, версия и ЯП
project(
    ${project_name}
    VERSION 1.0.0.0
    LANGUAGES CXX
)

# path to include/ and src/ dirs
set(lib_inc_dir include)
set(lib_src_dir src)

# обозначение всех *.hpp и *.cpp файлов из папок include/ и src/ 
file(GLOB lib_inc CONFIGURE_DEPENDS ${lib_inc_dir}/*.hpp)
file(GLOB lib_src CONFIGURE_DEPENDS ${lib_src_dir}/*.cpp)

# make lib
add_library(${target_library_name} ${lib_inc} ${lib_src})
set_target_properties(
    ${target_library_name}
    PROPERTIES
        OUTPUT_NAME ${library_name}
)

# path to main file
set(app_dir app)
set(app ${app_dir}/main.cpp)

# получаем бинарник с именем OUTPUT_NAME
add_executable(${target_project_name} ${app})
set_target_properties(
    ${target_project_name}
    PROPERTIES
        OUTPUT_NAME ${project_name}
)

# слинковать библиотеку и бинарник
target_link_libraries(${target_project_name} ${target_library_name})

#
#set(res_dir res)
#configure_file("${res_dir}/source.txt" source.txt COPYONLY)

# собрать ещё и тесты
add_subdirectory(tests)
