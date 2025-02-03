cmake_minimum_required(VERSION 3.10)

project(DEEPLEARNINGOPERATORS)

set(CMAKE_CXX_STANDARD 17)

# Find OpenCV
find_package(OpenCV REQUIRED)
find_package(nlohmann_json REQUIRED)
# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/Operators/include
    ${CMAKE_SOURCE_DIR}/utilities/include
    ${CMAKE_SOURCE_DIR}/Test_Operators/include
    ${OpenCV_INCLUDE_DIRS}
    D:/vcpkg/installed/x64-windows/include
)

# Set source files
set(SRCS
    ${CMAKE_SOURCE_DIR}/Operators/src/conv2d.cpp
    ${CMAKE_SOURCE_DIR}/Operators/src/dense.cpp
    ${CMAKE_SOURCE_DIR}/Operators/src/max_pooling2d.cpp
    ${CMAKE_SOURCE_DIR}/Operators/src/flatten.cpp
    ${CMAKE_SOURCE_DIR}/Operators/src/relu.cpp
    ${CMAKE_SOURCE_DIR}/Operators/src/softmax.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/utilities/src/file_io.cpp
    ${CMAKE_SOURCE_DIR}/utilities/src/load_json.cpp
    ${CMAKE_SOURCE_DIR}/utilities/src/logging.cpp
    ${CMAKE_SOURCE_DIR}/utilities/src/prediction.cpp
    ${CMAKE_SOURCE_DIR}/Test_Operators/src/testing.cpp
)


# Create executable
add_executable(DEEPLEARNINGOPERATORS ${SRCS})

# Link OpenCV
target_link_libraries(DEEPLEARNINGOPERATORS PRIVATE ${OpenCV_LIBS})
target_link_libraries(DEEPLEARNINGOPERATORS PRIVATE nlohmann_json::nlohmann_json)

# cmake_minimum_required(VERSION 3.10)
# project(DeepLearningOperators)

# # Set the C++ standard
# set(CMAKE_CXX_STANDARD 17)

# # Include directories
# include_directories(
#     utilities/include
#     Operators/include
#     D:/vcpkg/installed/x64-windows/include
# )

# # set(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE PATH "vcpkg toolchain file")

# find_package(nlohmann_json 3.11.3 REQUIRED)




# # Source files
# file(GLOB_RECURSE SRC_FILES src/*.cpp utilities/src/*.cpp Operators/src/*.cpp )

# # Find OpenCV
# find_package(OpenCV REQUIRED)

# # Include OpenCV headers
# include_directories(${OpenCV_INCLUDE_DIRS})

# # Add executable
# add_executable(DeepLearningOperators ${SRC_FILES})

# # Link OpenCV libraries
# target_link_libraries(DeepLearningOperators ${OpenCV_LIBS})
# target_link_libraries(example PRIVATE nlohmann_json::nlohmann_json)