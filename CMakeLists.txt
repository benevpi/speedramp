cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(speedramp)

pico_sdk_init()


add_executable(speedramp
    speedramp.c
)

# Pull in our pico_stdlib which aggregates commonly used features
target_link_libraries(speedramp pico_stdlib)

# create map/bin/h/uf2 file etc.
pico_add_extra_outputs(speedramp)
