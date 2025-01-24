cmake_minimum_required(VERSION 3.10)
project(math_lib_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include GoogleTest
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Enable code coverage
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# Add math_lib library
add_library(my_math math_lib/src/my_math.cpp)

# Create test executables
add_executable(math_lib_test test/math_lib_test.cpp)
target_link_libraries(math_lib_test my_math gtest gtest_main)

add_executable(edge_case_tests test_coverage/edge_case_tests.cpp)
target_link_libraries(edge_case_tests my_math gtest gtest_main)

# Add tests to CTest
enable_testing()
add_test(NAME math_lib_test COMMAND math_lib_test)
add_test(NAME edge_case_tests COMMAND edge_case_tests)

# Coverage target
add_custom_target(coverage
    COMMAND ${CMAKE_CTEST_COMMAND}
    COMMAND lcov --capture --directory . --output-file reports/coverage.info
    COMMAND genhtml reports/coverage.info --output-directory reports/coverage_report
    COMMENT "Generating coverage report"
)
