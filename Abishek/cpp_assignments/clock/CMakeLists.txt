# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project Name
project(ClockApp)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for header files
include_directories(include)

# Add the source files
set(SOURCES
    src/main.cpp
    src/alarm.cpp
    src/timer.cpp
    src/stopwatch.cpp
)

# Add the executable target
add_executable(ClockApp ${SOURCES})