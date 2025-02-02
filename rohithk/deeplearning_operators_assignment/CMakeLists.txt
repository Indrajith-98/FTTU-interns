cmake_minimum_required(VERSION 3.28.3)
project(DeepLearningOperators)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

find_package(nlohmann_json 3.11.3 REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(Operators/include utilities/include)
include_directories(${OpenCV_INCLUDE_DIRS} include)

configure_file(resources/input.png ${CMAKE_BINARY_DIR}/input.png COPYONLY)

add_library(CTensor Operators/src/ctensor.cpp)
add_library(Conv2d Operators/src/conv2d.cpp)
add_library(Utils utilities/src/utils.cpp)
add_library(BatchNorm Operators/src/batch_normalisation.cpp)
add_library(MaxPooling Operators/src/max_pooling.cpp)

target_include_directories(CTensor PUBLIC Operators/include)
target_include_directories(Conv2d PUBLIC Operators/include)
target_include_directories(Utils PUBLIC utilities/include)
target_include_directories(BatchNorm PUBLIC Operators/include)
target_include_directories(MaxPooling PUBLIC Operators/include)

target_link_libraries(Conv2d PUBLIC CTensor)
target_link_libraries(Utils PUBLIC CTensor)
target_link_libraries(MaxPooling PUBLIC Utils)
target_link_libraries(BatchNorm PUBLIC CTensor)

add_executable(main src/main.cpp)
target_link_libraries(main PUBLIC CTensor Conv2d Utils BatchNorm MaxPooling PRIVATE nlohmann_json::nlohmann_json ${OpenCV_LIBS})
