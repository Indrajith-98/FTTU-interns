cmake_minimum_required(VERSION 3.10)
project(DeepLearningOperators)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(
    Operators/include 
    utilities/include 
    Test_Operators/include
)

# 🔹 Define the main executable with all required source files
add_executable(main 
    src/main.cpp 
    src/model_parser.cpp
    utilities/src/file_io.cpp 
    utilities/src/logging.cpp 
    utilities/src/compare.cpp
    Operators/src/conv.cpp 
    Operators/src/relu.cpp 
    Operators/src/maxpool.cpp 
    Operators/src/softmax.cpp 
    Operators/src/add.cpp 
    Operators/src/matmul.cpp  
    utilities/src/compare.cpp # ✅ Ensure Add Layer is included!
)


# Test executable
# Test executables - One per test file
add_executable(test_conv Test_Operators/src/conv_test.cpp Operators/src/conv.cpp utilities/src/file_io.cpp utilities/src/compare.cpp)
add_executable(test_relu Test_Operators/src/relu_test.cpp Operators/src/relu.cpp utilities/src/file_io.cpp utilities/src/compare.cpp)
add_executable(test_maxpool Test_Operators/src/maxpool_test.cpp Operators/src/maxpool.cpp utilities/src/file_io.cpp utilities/src/compare.cpp)
add_executable(test_softmax Test_Operators/src/softmax_test.cpp Operators/src/softmax.cpp utilities/src/file_io.cpp utilities/src/compare.cpp)
add_executable(test_add Test_Operators/src/add_test.cpp Operators/src/add.cpp utilities/src/file_io.cpp utilities/src/compare.cpp)
add_executable(test_matmul Test_Operators/src/matmul_test.cpp Operators/src/matmul.cpp utilities/src/file_io.cpp utilities/src/compare.cpp)

