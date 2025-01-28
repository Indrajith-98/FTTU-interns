cmake_minimum_required(VERSION 3.10)
project(FashionMNIST)

set(CMAKE_CXX_STANDARD 17)

# ONNX Runtime Paths
set(ONNX_RUNTIME_DIR ${CMAKE_SOURCE_DIR}/onnxruntime)

include_directories(${ONNX_RUNTIME_DIR}/include)
link_directories(${ONNX_RUNTIME_DIR}/lib)

# OpenCV Configuration
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Executable and Linking
add_executable(FashionMNIST main.cpp)
target_link_libraries(FashionMNIST ${OpenCV_LIBS} onnxruntime)
