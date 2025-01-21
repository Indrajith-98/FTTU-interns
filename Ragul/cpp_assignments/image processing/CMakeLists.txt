cmake_minimum_required(VERSION 3.10)
 
# Set the project name
project(ImageProcessing)
 
# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set CMake path
set(CMAKE_PREFIX_PATH "C:/Users/ragul/opencv/build")

# set(OpenCV_DIR "D:/opencv/build")
include_directories(${PROJECT_SOURCE_DIR}/include)
 
# Collect all source files
file(GLOB_RECURSE SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/*.c
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)
# Add the executable
add_executable(ImageProcessing ${SOURCE_FILES})
 
# Find OpenCV package (if you are using OpenCV for image processing)
find_package(OpenCV REQUIRED)  
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(ImageProcessing ${OpenCV_LIBS})  