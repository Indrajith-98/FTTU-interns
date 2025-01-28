cmake_minimum_required(VERSION 3.10)
project(Deeplearning_Operators)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(
    utilities/include
    Operators/include
    Test_Operators/include
)

# Source files
file(GLOB_RECURSE SRC_FILES src/*.cpp utilities/src/*.cpp Operators/src/*.cpp Test_Operators/src/*.cpp)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Add executable
add_executable(myProject ${SRC_FILES})

# Link OpenCV libraries
target_link_libraries(myProject ${OpenCV_LIBS})