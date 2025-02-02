cmake_minimum_required(VERSION 3.10)
project(Z-Final_Op)

set(CMAKE_CXX_STANDARD 17)


include_directories(${CMAKE_SOURCE_DIR}/nlohmann)


# Add source files
add_executable(cnn_operators 
    main.cpp 
    utilities/src/utils.cpp 
    Operators/src/convolution.cpp
    Operators/src/relu.cpp
    Operators/src/dense.cpp
    Operators/src/softmax.cpp
    Operators/src/maxpool.cpp
    Operators/src/flatten.cpp
)

# Include directories
target_include_directories(cnn_operators PRIVATE 
    utilities/include 
    Operators/include
    Test_Operators/include
)

# Add OpenCV and JSON library if needed
# find_package(OpenCV REQUIRED)
# target_link_libraries(cnn_operators PRIVATE ${OpenCV_LIBS})
