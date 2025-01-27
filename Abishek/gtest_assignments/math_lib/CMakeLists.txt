# Minimum CMake version
cmake_minimum_required(VERSION 3.14)

# Project name and version
project(math_lib_project VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ensure a build type is set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Add the math_lib library (with correct path)
add_library(math_lib STATIC 
    src/my_math_updated.cpp  # Source file path for your math library
)

# Specify the include directories for the library
target_include_directories(math_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src  # Include path for header files
)

# Enable testing
enable_testing()

# Add GoogleTest submodule (with error check)
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/googletest)
    message(FATAL_ERROR 
        "GoogleTest submodule is not initialized. "
        "Run the following command to initialize it:\n"
        "    git submodule update --init --recursive"
    )
endif()
add_subdirectory(googletest)

# Add the test executable
add_executable(math_lib_test 
    test/test_my_math.cpp  # Path to your test file
)

# Link the test executable with math_lib and GoogleTest
target_link_libraries(math_lib_test PRIVATE math_lib gtest gtest_main)

# Apply coverage flags to test target only
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(math_lib_test PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
    target_link_options(math_lib_test PRIVATE --coverage)
endif()

# Automatically discover GoogleTest cases
include(GoogleTest)
gtest_discover_tests(math_lib_test)

# Add a custom target to generate code coverage reports
# Get the path to the gcovr executable from the virtual environment
find_program(GCOVR_PATH
    NAMES gcovr
    HINTS F:/MultiCoreWare/Environments/tvm/Scripts
)

if(NOT GCOVR_PATH)
    message(FATAL_ERROR "gcovr executable not found in the virtual environment. Please activate your venv.")
endif()

set(COVERAGE_OUTPUT_DIR F:/MultiCoreWare/Submissions/FTTU-interns/Abishek/gtest_assignments/math_lib/reports)

file(MAKE_DIRECTORY ${COVERAGE_OUTPUT_DIR})



add_custom_target(coverage
COMMAND ${GCOVR_PATH} -r ${CMAKE_CURRENT_SOURCE_DIR} --html --html-details -o ${COVERAGE_OUTPUT_DIR}/coverage.html
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating code coverage report with gcovr..."
)
