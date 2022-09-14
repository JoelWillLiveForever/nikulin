cmake_minimum_required(VERSION 3.12)

set(target_suffix "C_PROJECT")

set(project_name "PolygonTD")
set(target_project_name "${project_name}-${target_suffix}")

set(library_name "foo")
set(target_library_name "${library_name}-${target_suffix}")

project(
    ${project_name}
    VERSION 1.0.0.0
    LANGUAGES C
)

set(lib_inc_dir include)
set(lib_src_dir src)

file(GLOB lib_inc CONFIGURE_DEPENDS ${lib_inc_dir}/*.h)
file(GLOB lib_src CONFIGURE_DEPENDS ${lib_src_dir}/*.c)

add_library(${target_library_name} ${lib_inc} ${lib_src})
set_target_properties(
    ${target_library_name}
    PROPERTIES
        OUTPUT_NAME ${library_name}
)

set(app_dir app)
set(app ${app_dir}/main.c)

add_executable(${target_project_name} ${app})
set_target_properties(
    ${target_project_name}
    PROPERTIES
        OUTPUT_NAME ${project_name}
)

target_link_libraries(${target_project_name} ${target_library_name})
