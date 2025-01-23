cmake_minimum_required(VERSION 3.10)
project(ImagePreprocessor)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/cropping.cpp
    src/grayscale.cpp
    src/normalize.cpp
    src/rotate.cpp
    src/resize.cpp
)

set(OpenCV_DIR "C:/Users/Abishek R/Downloads/opencv/build")
# Find OpenCV
find_package(OpenCV REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Add executable
add_executable(ImagePreprocessor ${SOURCES})

# Link OpenCV libraries
target_link_libraries(ImagePreprocessor ${OpenCV_LIBS})