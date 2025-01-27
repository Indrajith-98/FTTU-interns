cmake_minimum_required(VERSION 3.10)
project(MyMathProject)

add_subdirectory(external/googletest)

enable_testing()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "Building with coverage flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -g -O0")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -g -O0")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_SOURCES
    src/my_math.cpp
)

set(TEST_SOURCES
    test_coverage/test_my_math.cpp
)

add_executable(my_math_test ${SRC_SOURCES} ${TEST_SOURCES})

target_include_directories(my_math_test PRIVATE include)
target_link_libraries(my_math_test gtest gtest_main pthread)

add_test(NAME MyMathTest COMMAND my_math_test)
