cmake_minimum_required(VERSION 3.31)

include(pico_sdk_import.cmake)

project(blink C CXX ASM)
#project(blink)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

# init pico SDK
pico_sdk_init()

# add exec
add_executable(blink
  blink.c
)

# Link to std lib
target_link_libraries(blink pico_stdlib)

# Output, UF2 file
pico_add_extra_outputs(blink)
