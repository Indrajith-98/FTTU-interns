cmake_minimum_required(VERSION 3.10)
project(OpenCVAssignment)

# Set the path for OpenCV
set(OpenCV_DIR C:/o_p_e_n_C_V/opencv/build)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include OpenCV and project header files
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR})  # Assuming the source code is in the current directory

# Add the source files for the project
add_executable(OpenCVAssignment main.cpp ImageProcessor.cpp)

# Link OpenCV libraries
target_link_libraries(OpenCVAssignment ${OpenCV_LIBS})
