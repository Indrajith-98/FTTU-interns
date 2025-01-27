cmake_minimum_required(VERSION 3.10)

# Project name
project(ClockApplication)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/alarm.cpp
    src/stopwatch.cpp
    src/timer.cpp
    main.cpp
)

# Add executable
add_executable(ClockApplication ${SOURCES})
