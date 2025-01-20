cmake_minimum_required(VERSION 3.10)

# Set the project name
project(ImageProcessing)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 
set(OpenCV_DIR D:/opencv/build)
 
set(ImageProcessor.cpp)
# Add the executable
add_executable(ImageProcessor ImageProcessor.cpp)

# Find OpenCV package (if you are using OpenCV for image processing)
find_package(OpenCV REQUIRED)  
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(ImageProcessor ${OpenCV_LIBS})  