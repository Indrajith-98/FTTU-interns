# # Minimum CMake version
# cmake_minimum_required(VERSION 3.14)

# # Project name and version
# project(GTestExample VERSION 1.0 LANGUAGES CXX)

# # Set C++ standard
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# # Add the library (math_lib)
# add_library(math_lib math_lib/src/my_math.cpp)

# # Specify the include directories for the library
# target_include_directories(math_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/math_lib/src)

# # Enable testing
# enable_testing()

# # Add GoogleTest using FetchContent
# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/refs/heads/main.zip
# )
# # Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

# # Add the test executable
# add_executable(test_math_lib ${CMAKE_CURRENT_SOURCE_DIR}/test_math_lib.cpp)
# message(STATUS "Test sources: ${CMAKE_CURRENT_SOURCE_DIR}/test_math_lib.cpp")



# # Link the test executable with math_lib and GoogleTest
# target_link_libraries(test_math_lib PRIVATE math_lib gtest gtest_main)

# # Add the test to CTest
# add_test(NAME MathLibTests COMMAND test_math_lib)


# Minimum CMake version
cmake_minimum_required(VERSION 3.14)

# Project name and version
project(GTestExample VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the library (math_lib)
add_library(math_lib math_lib/src/my_math.cpp)

# Specify the include directories for the library
target_include_directories(math_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/math_lib/src)

# Enable testing
enable_testing()

# Add GoogleTest using FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add the test executables
add_executable(test_math_lib ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/unit_test_math_lib.cpp)
add_executable(edge_test_math_lib ${CMAKE_CURRENT_SOURCE_DIR}/edge_test/edge_test_math_lib.cpp)

# Link the test executables with math_lib and GoogleTest
target_link_libraries(test_math_lib PRIVATE math_lib gtest gtest_main)
target_link_libraries(edge_test_math_lib PRIVATE math_lib gtest gtest_main)

# Add the tests to CTest
add_test(NAME MathLibTests COMMAND test_math_lib)
add_test(NAME EdgeMathLibTests COMMAND edge_test_math_lib)

# Optionally, you can set additional flags or parameters for testing
# to handle test output, etc.
