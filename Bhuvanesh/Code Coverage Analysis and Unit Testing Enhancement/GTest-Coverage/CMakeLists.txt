cmake_minimum_required(VERSION 3.10)
project(GTest-Coverage)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest REQUIRED)

enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/include)  

set(SOURCE_FILES
    my_math.cpp   
    test_my_program.cpp
)

set(CMAKE_CXX_FLAGS "--coverage")



add_executable(runTests ${SOURCE_FILES})


target_link_libraries(runTests GTest::GTest GTest::Main pthread)


add_test(NAME my_test COMMAND runTests)
