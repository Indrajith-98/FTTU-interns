cmake_minimum_required(VERSION 3.10)

# Project name and version
project(ImageProcessing)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(OpenCV_DIR "C:/Users/7501/Downloads/opencv/build")
# Find OpenCV
find_package(OpenCV REQUIRED)
 
set(SOURCES 
src/grayscale.cpp
src/randomcrop.cpp
src/randomhorizontal.cpp
src/imageblur.cpp
src/edgedetection.cpp
main.cpp)


# Include OpenCV headers
include_directories(include ${OpenCV_INCLUDE_DIRS})
 
# Add executable
add_executable(ImageProcessing ${SOURCES})
 
# Link OpenCV libraries
target_link_libraries(ImageProcessing ${OpenCV_LIBS})