cmake_minimum_required(VERSION 3.10)
project(FashionMNIST)

set(CMAKE_CXX_STANDARD 17)

# ONNX Runtime Paths
set(ONNX_RUNTIME_DIR ${CMAKE_SOURCE_DIR}/onnxruntime)
include_directories(${ONNX_RUNTIME_DIR}/include)
link_directories(${ONNX_RUNTIME_DIR}/lib)

# OpenCV Configuration
# find_package(OpenCV REQUIRED)
# include_directories(${OpenCV_INCLUDE_DIRS})

# Set Torch_DIR manually
# set(Torch_DIR "/mnt/d/MulticoreWare/libtorch/share/cmake/Torch")  # WSL Path
# find_package(Torch REQUIRED)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# JSON Parser
find_package(nlohmann_json REQUIRED)

# Executable and Linking
add_executable(FashionMNIST onnx_json_parser.cpp base64.cpp)
# target_link_libraries(FashionMNIST ${OpenCV_LIBS} onnxruntime ${TORCH_LIBRARIES} nlohmann_json::nlohmann_json)
target_link_libraries(FashionMNIST onnxruntime nlohmann_json::nlohmann_json)


set_property(TARGET FashionMNIST PROPERTY CXX_STANDARD 17)
