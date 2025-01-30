cmake_minimum_required(VERSION 3.10)

# Project name
project(math_lib_ver1)

# Enable testing
enable_testing()

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Set compiler flags for debugging and coverage
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    src/my_math.cpp
)

# Add test files
set(TEST_SOURCES
    test/test_my_math.cpp
)

# Fetch Google Test from GitHub using FetchContent
include(FetchContent)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0  # Specify the version here
)
FetchContent_MakeAvailable(gtest)

# Add the library (your math library)
add_library(src ${SOURCES})

# Add the executable for tests
add_executable(test_my_math ${TEST_SOURCES})

# Link Google Test to the test executable
target_link_libraries(test_my_math src gtest gtest_main)

# Register the test with CTest
add_test(NAME MathLibTest COMMAND test_my_math)
