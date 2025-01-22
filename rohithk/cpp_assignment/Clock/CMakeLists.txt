cmake_minimum_required(VERSION 3.28.3)

project( clock_project )

add_executable(main main.cpp )

include_directories(include)

add_library(Clock src/Clock.cpp)

target_include_directories(Clock PUBLIC include)

target_link_libraries(main PRIVATE Clock)