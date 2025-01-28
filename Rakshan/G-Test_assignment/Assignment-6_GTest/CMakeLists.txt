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

# Ensure the googletest content is available
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

# Add the test executable for TestExample.cpp
set(TEST_SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/TestExample.cpp)
message(STATUS "Test sources: ${TEST_SOURCE_PATH}")
if(EXISTS ${TEST_SOURCE_PATH})
    add_executable(TestExample ${TEST_SOURCE_PATH})
else()
    message(FATAL_ERROR "Test file not found: ${TEST_SOURCE_PATH}")
endif()

# Link the test executable with math_lib and GoogleTest
target_link_libraries(TestExample PRIVATE math_lib gtest gtest_main)

# Add the test to CTest
add_test(NAME MathLibTests COMMAND TestExample)

# Add the test executable for coverage tests
set(COVERAGE_TEST_PATH ${CMAKE_CURRENT_SOURCE_DIR}/test_coverage/coverage_tests.cpp)
message(STATUS "Coverage test sources: ${COVERAGE_TEST_PATH}")
if(EXISTS ${COVERAGE_TEST_PATH})
    add_executable(CoverageExample ${COVERAGE_TEST_PATH})
else()
    message(FATAL_ERROR "Coverage test file not found: ${COVERAGE_TEST_PATH}")
endif()

# Link the coverage test executable with math_lib and GoogleTest
target_link_libraries(CoverageExample PRIVATE math_lib gtest gtest_main)

# Add the coverage test to CTest
add_test(NAME CoverageTests COMMAND CoverageExample)

# Enable code coverage flags for GCC/Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(TestExample PRIVATE --coverage)
    target_link_options(TestExample PRIVATE --coverage)

    target_compile_options(CoverageExample PRIVATE --coverage)
    target_link_options(CoverageExample PRIVATE --coverage)
endif()

# Output coverage instructions (optional helper)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "Run 'ctest' followed by 'gcov/lcov' commands to generate coverage reports.")
endif()

#########################
# # Minimum CMake version
# cmake_minimum_required(VERSION 3.14)

# # Project name and version
# project(GTestExample VERSION 1.0 LANGUAGES CXX)

# # Set C++ standard
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# # Set build type to Debug to include debug symbols
# if(NOT CMAKE_BUILD_TYPE)
#     set(CMAKE_BUILD_TYPE Debug)
# endif()

# # Add the library (math_lib)
# add_library(math_lib math_lib/src/my_math.cpp)

# # Specify the include directories for the library
# target_include_directories(math_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/math_lib/src)

# # Enable testing
# enable_testing()

# # Add GoogleTest using FetchContent
# include(FetchContent)
# FetchContent_Declare(
#     googletest
#     URL https://github.com/google/googletest/archive/refs/heads/main.zip
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

# # Add the test executable (make sure this comes before the coverage target)
# add_executable(TestExample ${CMAKE_CURRENT_SOURCE_DIR}/TestExample.cpp)
# message(STATUS "Test sources: ${CMAKE_CURRENT_SOURCE_DIR}/TestExample.cpp")

# # Link the test executable with math_lib and GoogleTest
# target_link_libraries(TestExample PRIVATE math_lib gtest gtest_main)

# # Add the test to CTest
# add_test(NAME MathLibTests COMMAND TestExample)

# # Add a custom target to generate the coverage report
# if(MSVC)
#     find_program(OPENCOVERAGE_PATH OpenCppCoverage)
#     if(OPENCOVERAGE_PATH)
#         add_custom_target(coverage
#             COMMAND "${OPENCOVERAGE_PATH}" 
#                 --sources "${CMAKE_SOURCE_DIR}/math_lib/src" 
#                 --export_type html:"${CMAKE_BINARY_DIR}/coverage_report" 
#                 -- ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/TestExample.exe
#             WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#             COMMENT "Generating code coverage report with OpenCppCoverage"
#             USES_TERMINAL
#             DEPENDS TestExample
#         )
#     else()
#         message(WARNING "OpenCppCoverage not found! Coverage target will not be available.")
#     endif()
# endif()
