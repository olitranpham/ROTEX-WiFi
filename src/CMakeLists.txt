cmake_minimum_required(VERSION 3.13)

# set board (Pico 2 W)
set(PICO_BOARD pico2_w)

# Import Pico SDK
include(pico_sdk_import.cmake)

project(shoulder_shield C CXX ASM)

# Initialize SDK
pico_sdk_init()

add_executable(shoulder_shield
    main.c
    Pico_BNO08x_multi.c
    sh2.c
    sh2_SensorValue.c
    sh2_util.c
    shtp.c
    wireless_transfer.c
)

pico_enable_stdio_usb(shoulder_shield 1)
pico_enable_stdio_uart(shoulder_shield 0)

target_include_directories(shoulder_shield PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(shoulder_shield
    pico_stdlib
    hardware_spi
    hardware_gpio
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip
)

pico_add_extra_outputs(shoulder_shield)