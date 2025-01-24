cmake_minimum_required(VERSION 3.10)

# Set the project name
project(OpenCVProject)

# Find OpenCV package

find_package(OpenCV REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})
# Add the executable
add_executable(OpenCVProject main.cpp)

# Link OpenCV libraries
target_link_libraries(OpenCVProject ${OpenCV_LIBS})
include(CPack)