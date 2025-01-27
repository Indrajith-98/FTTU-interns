cmake_minimum_required(VERSION 3.10)

# Project name
project(MyMathLib)

# Enable testing
enable_testing()

# Add the math library
add_library(math_lib math_lib/src/my_math.cpp)
target_include_directories(math_lib PUBLIC math_lib/include)

# Add Google Test
find_package(GTest REQUIRED)

# Add the test executable
add_executable(MyMathTests ${CMAKE_SOURCE_DIR}/tests/my_math_test.cpp)
target_include_directories(MyMathTests PRIVATE math_lib/include)
target_link_libraries(MyMathTests math_lib GTest::gtest GTest::gtest_main)

# Add tests to CTest
add_test(NAME MyMathTests COMMAND MyMathTests)

# Enable coverage (optional, for GCC/Clang)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(math_lib PRIVATE --coverage)
    target_link_libraries(math_lib PRIVATE --coverage)
endif()

# Add a custom target to generate code coverage (without lcov/genhtml)
add_custom_target(
    coverage
    COMMENT "Generating code coverage report"
)

# Optionally, add a post-test command to automatically open the report
add_custom_target(
    open_coverage_report
    COMMENT "Opening code coverage report"
)

# Ensure that coverage is run after tests are executed
add_dependencies(coverage MyMathTests)
add_dependencies(open_coverage_report coverage)
