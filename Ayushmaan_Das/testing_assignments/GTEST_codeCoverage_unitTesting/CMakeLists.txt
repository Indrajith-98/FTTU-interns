cmake_minimum_required(VERSION 3.10)
project(MyMathProject)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "Building with coverage flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    src/my_math.cpp
    main.cpp  
)

add_executable(my_math ${SOURCES})

target_include_directories(my_math PRIVATE include)