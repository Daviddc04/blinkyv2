cmake_minimum_required(VERSION 3.13)

# Set the project name and C++ standard
project(blinkyv2 C CXX ASM)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)


# Import PICO_SDK_PATH from environment if not passed as a CMake variable
if(NOT DEFINED PICO_SDK_PATH AND DEFINED ENV{PICO_SDK_PATH})
    set(PICO_SDK_PATH "$ENV{PICO_SDK_PATH}")
endif()

# Require it now
if(NOT DEFINED PICO_SDK_PATH)
    message(FATAL_ERROR "PICO_SDK_PATH is not set. Set it as a CMake option (-DPICO_SDK_PATH=...) or in the environment.")
endif()

# Make sure it is absolute
get_filename_component(PICO_SDK_PATH "${PICO_SDK_PATH}" ABSOLUTE)


# Import Pico SDK
include("${PICO_SDK_PATH}/external/pico_sdk_import.cmake")


# Initialize the SDK
pico_sdk_init()

# Add executable
add_executable(blinkyv2
        src/main.cpp
)

# Link Pico libraries
target_link_libraries(blinkyv2
        pico_stdlib
)

# Enable USB output, disable UART
pico_enable_stdio_usb(blinkyv2 1)
pico_enable_stdio_uart(blinkyv2 0)

# Use elf2uf2 instead of picotool for UF2 conversion (override any cached value)
set(PICO_USE_PICOTOOL OFF CACHE BOOL "Use picotool for UF2 conversion" FORCE)

# Ensure the produced executable has a .elf extension (helps if picotool is ever used)
set_target_properties(blinkyv2 PROPERTIES SUFFIX ".elf")


# Create UF2 file
pico_add_extra_outputs(blinkyv2)