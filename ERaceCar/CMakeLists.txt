cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Load toolchain file - CRITICAL for cross-compilation
# This must be done BEFORE project() for CMake to process it correctly
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    # Use CMAKE_CURRENT_SOURCE_DIR which is available and points to the directory
    # containing this CMakeLists.txt file
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/gcc-arm-none-eabi.cmake" CACHE FILEPATH "Toolchain file")
endif()

# Explicitly include the toolchain file to ensure it's processed
# This is necessary even if CMAKE_TOOLCHAIN_FILE is set, as CMake may not
# automatically process it when compilers are specified via command line
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/gcc-arm-none-eabi.cmake")

# CRITICAL: Set this BEFORE project() to prevent CMake from trying to link executables
# during compiler detection. This is essential for cross-compilation.
# This should already be set in the toolchain file, but we set it here as well
# to ensure it's applied even if the toolchain file wasn't processed correctly.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY CACHE INTERNAL "")

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME ERaceCar)


# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Update link flags with project name for map file (now that project() has been called)
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,-Map=${CMAKE_PROJECT_NAME}.map")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -Wl,-Map=${CMAKE_PROJECT_NAME}.map")

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME}
        Chassic/chassic.c
        Chassic/chassic.h
        Chassic/motor.c
        Chassic/motor.h
        Chassic/mpu6050.c
        Chassic/mpu6050.h
        Chassic/pid.c
        Chassic/pid.h
        Chassic/line.c
        Chassic/line.h)

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    Chassic
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
