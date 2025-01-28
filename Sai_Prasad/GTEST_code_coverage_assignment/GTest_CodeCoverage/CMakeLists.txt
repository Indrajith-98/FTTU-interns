cmake_minimum_required(VERSION 3.10)
project(GTest_CodeCoverage)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src)
# add_library(MathLib src/my_math.cpp)
# Find GoogleTest package
find_package(GTest REQUIRED)

# Enable testing
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} --coverage")
# set(SOURCE_FILES 
#     src/my_math.cpp # Your program source file
# )
# Add your test files
# set(TEST_FILES
#     tests/test_my_program.cpp  # Your test files
# )

# add_executable(my_program src/my_math.cpp)
# Add an executable for the tests
add_executable(runTests tests/test_my_program.cpp src/my_math.cpp)

# Link GoogleTest libraries and pthread (required by GTest)
target_link_libraries(runTests GTest::GTest GTest::Main pthread)

# Add tests to CTest
add_test(NAME MyMathTest COMMAND runTests)
