
set(OpenCV_SKIP_QT TRUE)
# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(ImagePreprocessing)

# Find the OpenCV package
find_package(OpenCV REQUIRED)

# Specify the source files

set(SOURCE_FILES main.cpp)


# Add an executable to the project
add_executable(ImagePreprocessing ${SOURCE_FILES})

# Link OpenCV to your project
target_link_libraries(ImagePreprocessing ${OpenCV_LIBS})

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})
