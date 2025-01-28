cmake_minimum_required(VERSION 3.10)

# Project name
project(Conv2DProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(OpenCV_DIR F:/opencv/opencv/build)

find_package(OpenCV REQUIRED)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/Operators/include
    ${PROJECT_SOURCE_DIR}/Test_Operators/include
    ${PROJECT_SOURCE_DIR}/utilities/include
    ${PROJECT_SOURCE_DIR}/include
)

# Source files
file(GLOB_RECURSE OPERATORS_SRC
    ${PROJECT_SOURCE_DIR}/Operators/src/*.cpp
)

file(GLOB_RECURSE TEST_OPERATORS_SRC
    ${PROJECT_SOURCE_DIR}/Test_Operators/src/*.cpp
)

file(GLOB_RECURSE UTILITIES_SRC
    ${PROJECT_SOURCE_DIR}/utilities/src/*.cpp
)

file(GLOB_RECURSE MAIN_SRC
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

# Add executable
add_executable(Conv2DApp
    ${OPERATORS_SRC}
    ${TEST_OPERATORS_SRC}
    ${UTILITIES_SRC}
    ${MAIN_SRC}
)

# Link necessary libraries
target_link_libraries(Conv2DApp ${OpenCV_LIBS})
