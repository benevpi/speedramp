cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(speedramp)

pico_sdk_init()


add_executable(speedramp
    speedramp.c
)

# Pull in our pico_stdlib which aggregates commonly used features
target_link_libraries(speedramp pico_stdlib)

#set uart on USB
pico_enable_stdio_usb(speedramp 1)
pico_enable_stdio_uart(speedramp 0)

# create map/bin/h/uf2 file etc.
pico_add_extra_outputs(speedramp)
