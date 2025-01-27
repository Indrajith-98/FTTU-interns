cmake_minimum_required(VERSION 3.10)
 
project(GTESTEG)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set debug build type by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
 
# Add coverage flags for Debug build
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -g")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage -g")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()
 
# Add GoogleTest
add_subdirectory(googletest)
 
# Add source files
add_library(MyMath STATIC src/my_math.cpp)
target_include_directories(MyMath PUBLIC include)

# Create a test executable
add_executable(MyTest main.cpp)
target_link_libraries(MyTest MyMath gtest gtest_main)
 
# Enable testing
enable_testing()
add_test(NAME MyTest COMMAND MyTest)


# Add coverage target
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    find_program(LCOV lcov)
    if(LCOV)
        add_custom_target(coverage
            COMMAND ${LCOV} --directory . --capture --output-file coverage.info
            COMMAND ${LCOV} --remove coverage.info '/usr/*' '/googletest/*' --output-file coverage.info
            COMMAND genhtml coverage.info --output-directory coverage
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating code coverage report"
        )
    else()
        message(WARNING "lcov not found! Coverage target will not be available.")
    endif()
endif()