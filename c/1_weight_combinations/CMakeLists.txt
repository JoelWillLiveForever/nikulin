cmake_minimum_required(VERSION 3.12)

project(
    "WeightCombinations"
    VERSION 1.0.0.0
    LANGUAGES C
)

set(apps 
    weight_combinations.c
    weight_combinations_detail.c
)

foreach(app ${apps})
    get_filename_component(app_we ${app} NAME_WE)
    add_executable(${app_we} ${app})
endforeach(app ${apps})
