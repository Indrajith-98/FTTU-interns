# Minimum CMake version
cmake_minimum_required(VERSION 3.14)

# Project name and version
project(math_lib_project VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the math_lib library (with correct path)
add_library(math_lib STATIC math_lib/src/updated_my_math.cpp)
# add_library(math_lib STATIC math_lib/src/my_math.cpp)

# Specify the include directories for the library
target_include_directories(math_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/math_lib/src)

# Enable testing
enable_testing()

# Add GoogleTest submodule (assuming you have already added it via git)
add_subdirectory(googletest)

# Add the test executables
add_executable(math_lib_test test/math_lib_test.cpp)
add_executable(edge_case_tests test_coverage/edge_case_tests.cpp)

# Link the test executables with math_lib and GoogleTest
target_link_libraries(math_lib_test PRIVATE math_lib gtest gtest_main)
target_link_libraries(edge_case_tests PRIVATE math_lib gtest gtest_main)

# Add the tests to CTest
add_test(NAME math_lib_test COMMAND math_lib_test)
add_test(NAME edge_case_tests COMMAND edge_case_tests)

# Coverage flags (only for GCC/MinGW)
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

# Coverage report (optional)
# add_custom_target(coverage
#     COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
#     COMMAND lcov --capture --directory . --output-file coverage.info
#     COMMAND genhtml coverage.info --output-directory ${CMAKE_BINARY_DIR}/reports/coverage_report
#     COMMENT "Generating coverage report"
# )

add_custom_target(coverage
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMAND gcov -r . -o build math_lib_test.cpp
    COMMAND genhtml *.gcov --output-directory ${CMAKE_BINARY_DIR}/reports/coverage_report
    COMMENT "Generating coverage report"
)
