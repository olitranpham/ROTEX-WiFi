cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico_w)

# Include the SDK
include(src/pico_sdk_import.cmake)

# Project name
project(Shoulder_Shield C CXX ASM)

# Set C and C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

# Add include directories
include_directories(include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add the source directory
add_subdirectory(src)