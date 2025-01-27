cmake_minimum_required(VERSION 3.10)

# Project name
project(ImageProcessing)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(OpenCV_DIR F:/opencv/opencv/build)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/Grayscale.cpp
    src/Invert.cpp
    src/Brightness.cpp
    src/Normalization.cpp
    src/GaussianBlur.cpp
    main.cpp
)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link OpenCV libraries
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})