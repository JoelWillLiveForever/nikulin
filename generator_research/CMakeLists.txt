cmake_minimum_required(VERSION 3.14)
project(generator_research
    LANGUAGES C CXX
)

add_custom_target (JupyterNotebook SOURCES generator_research.ipynb)

set(sources main.cpp
    samples.cpp
    samples.hpp
)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_executable(GeneratorResearch)
target_sources(GeneratorResearch PRIVATE ${sources})
target_link_libraries(GeneratorResearch
    PRIVATE
        random::random
        Boost::program_options
)
target_precompile_headers(GeneratorResearch REUSE_FROM classes)
