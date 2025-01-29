cmake_minimum_required(VERSION 3.28.3)
project(DeepLearningOperators)

# Include directories
include_directories(Operators/include utilities/include)

# Create libraries
add_library(CTensor Operators/src/ctensor.cpp)
add_library(Conv2d Operators/src/conv2d.cpp)
add_library(Utils utilities/src/utils.cpp)

# Set include directories for libraries
target_include_directories(CTensor PUBLIC Operators/include)
target_include_directories(Conv2d PUBLIC Operators/include)
target_include_directories(Utils PUBLIC utilities/include)

# Ensure proper linking
target_link_libraries(Conv2d PUBLIC CTensor)
target_link_libraries(Utils PUBLIC CTensor)

# Main executable
add_executable(main src/main.cpp)
target_link_libraries(main PUBLIC CTensor Conv2d Utils)
