cmake_minimum_required(VERSION 3.10)
project(OpenCVExample)

# Set OpenCV directory path
set(OpenCV_DIR "C:/opencv/build/x64/vc16/lib")  # Adjust to match your OpenCV installation

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include directories for OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# Add executable
add_executable(OpenCVExample main.cpp) 

# Link OpenCV libraries
target_link_libraries(OpenCVExample ${OpenCV_LIBS})
