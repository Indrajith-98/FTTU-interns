
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(DeepLearningOperators)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include FetchContent for external dependencies
include(FetchContent)

# Set OpenCV path (Update this path if necessary)
set(OpenCV_DIR C:/o_p_e_n_C_V/opencv/build)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include OpenCV headers explicitly
include_directories(${OpenCV_INCLUDE_DIRS})

# Fetch nlohmann/json library
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.10.5  # You can specify the version you need
)

FetchContent_MakeAvailable(nlohmann_json)

# Include directories
include_directories(utilities/include Operators/include)

# Create a library for ImageReader
add_library(image_reader utilities/src/image_reader.cpp)
target_include_directories(image_reader PUBLIC utilities/include)

# Create a library for JSON handler
add_library(json_handler utilities/src/json_handler.cpp)
target_include_directories(json_handler PUBLIC 
    utilities/include 
    ${nlohmann_json_SOURCE_DIR}/single_include
)

# Create a library for TensorOps
add_library(tensor_ops utilities/src/tensor_ops.cpp)
target_include_directories(tensor_ops PUBLIC 
    utilities/include 
    ${nlohmann_json_SOURCE_DIR}/single_include
)
target_include_directories(tensor_ops PUBLIC utilities/include)


add_library(conv Operators/src/conv.cpp)
target_include_directories(conv PUBLIC Operators/include)

add_library(max_pool Operators/src/max_pool.cpp)
target_include_directories(max_pool PUBLIC Operators/include)

add_library(flatten Operators/src/flatten.cpp)
target_include_directories(flatten PUBLIC Operators/include)

add_library(dense Operators/src/dense.cpp)
target_include_directories(dense PUBLIC Operators/include)

add_library(cnn_functions src/cnn_functions.cpp)
target_include_directories(cnn_functions PUBLIC include)

include_directories(${nlohmann_json_SOURCE_DIR}/include)


# Add the executable
add_executable(main src/main.cpp)

# Link the library and dependencies to the executable
target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json image_reader json_handler tensor_ops conv max_pool flatten dense cnn_functions ${OpenCV_LIBS})
