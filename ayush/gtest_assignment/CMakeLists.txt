# Set minimum required CMake version
cmake_minimum_required(VERSION 3.15)

# Project name
project(math_lib)

# Enable testing
enable_testing()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "C:/Users/sendm/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Add source files
add_library(math_lib src/my_math.cpp)

# Add unit tests
add_executable(test_math test_coverage/test_my_math.cpp)

# Link GoogleTest and math_lib to the test executable
find_package(GTest REQUIRED)
target_link_libraries(test_math PRIVATE math_lib GTest::gtest GTest::gtest_main)
target_include_directories(test_math PRIVATE ${PROJECT_SOURCE_DIR}/src)

# Add tests to the CTest suite
add_test(NAME UnitTests COMMAND test_math)
