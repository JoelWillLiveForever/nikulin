cmake_minimum_required(VERSION 3.12)

project(GlobalProject
    VERSION 1.0.0.0
    LANGUAGES C CXX
)

# Build all projects
# C:
add_subdirectory(c/1_weight_combinations)
add_subdirectory(c/3_polygon_traversal_direction)

# CPP:
add_subdirectory(cpp/1_weight_combinations)
add_subdirectory(cpp/3_polygon_traversal_direction)

# C & CPP:
add_subdirectory(2_pi_monte_carlo)
