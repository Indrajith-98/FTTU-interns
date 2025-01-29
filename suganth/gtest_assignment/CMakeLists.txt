

# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(MathLib)

# Enable testing
enable_testing()

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)


# Enable coverage flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

# Include directories (modify this if necessary)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add source files (modify this with your source files)
set(SOURCES
    math_lib/src/my_math.cpp
)

# Add test files (modify this with your test files)
set(TEST_SOURCES
    test_coverage/math_lib_test.cpp
)

# Fetch Google Test from GitHub using FetchContent
include(FetchContent)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0  # You can specify the version here, or use 'master' for the latest
)
FetchContent_MakeAvailable(gtest)
# Add the library (your math library)
add_library(math_lib ${SOURCES})

# Add the executable for tests
add_executable(math_lib_test ${TEST_SOURCES})

# Link Google Test to the test executable (modify this if necessary)
target_link_libraries(math_lib_test math_lib gtest gtest_main)
