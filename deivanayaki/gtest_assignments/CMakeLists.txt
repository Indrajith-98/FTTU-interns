cmake_minimum_required(VERSION 3.17)
project(GTESTASS)

enable_testing()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

add_library(MathLib src/my_math.cpp)

target_include_directories(MathLib PUBLIC src)

add_subdirectory(googletest)

add_executable(AllTests tests/my_math_tests.cpp tests/run_tests.cpp)
target_link_libraries(AllTests PRIVATE MathLib gtest gtest_main)

set(GTEST_OUTPUT "xml:${CMAKE_BINARY_DIR}/tests/results.xml")
add_test(NAME AllTests COMMAND AllTests --gtest_output=${GTEST_OUTPUT} --gtest_color=yes)
