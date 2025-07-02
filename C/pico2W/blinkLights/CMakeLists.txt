include(pico_sdk_import.cmake)

project(picow_blink C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_SDK_PATH ${CMAKE_SOURCE_DIR}/pico-sdk)

pico_sdk_init()

add_executable(picow_blink)
    main.c
)
target_link_libraries(picow_blink pico_stdlib cyw43_drv)
pico_add_extra_outputs(picow_blink)
