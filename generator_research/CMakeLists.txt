cmake_minimum_required(VERSION 3.14)
project(generator_research
    LANGUAGES C CXX
)

set(sources main.cpp
    samples.cpp
    samples.hpp
)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_executable(generator_research)
target_sources(generator_research PRIVATE ${sources})
target_link_libraries(generator_research 
    PRIVATE 
    random::random
    Boost::program_options
)
target_precompile_headers(generator_research REUSE_FROM classes)