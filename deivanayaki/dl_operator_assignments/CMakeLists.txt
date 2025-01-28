# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project Name
project(DLOPL)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add the source directories
include_directories(Operators/include)  # Include Operators header files
include_directories(extern)  # Include extern directory for json.hpp

# Add the source files
set(SOURCES
    Operators/src/conv.cpp
    Operators/src/prelu.cpp
    Operators/src/batch_norm.cpp
    Operators/src/max_pool.cpp
    Operators/src/flatten.cpp
    Operators/src/dense.cpp 
    Operators/src/selu.cpp
    Operators/src/softmax.cpp
    utils/src/FileUtils.cpp
    utils/src/ResultUtils.cpp
    utils/src/IntermediateResultUtils.cpp
    utils/src/LogUtils.cpp
    Test_Operators/src/conv_test.cpp
    Test_Operators/src/prelu_test.cpp
    Test_Operators/src/batch_norm_test.cpp
    Test_Operators/src/max_pool_test.cpp
    Test_Operators/src/flatten_test.cpp
    Test_Operators/src/dense_test.cpp
    main.cpp                # Add your main.cpp file
)

# Create the executable
add_executable(DLOPL ${SOURCES})

# If you need to link with external libraries, you can add them here
# Example: target_link_libraries(ModelParser <library_name>)
