
cmake_minimum_required(VERSION 3.28.3)
project(DeepLearningOperators)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

find_package(nlohmann_json 3.11.3 REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(Operators/include utilities/include)
include_directories(${OpenCV_INCLUDE_DIRS} include)

configure_file(resources/input.png ${CMAKE_BINARY_DIR}/input.png COPYONLY)

add_library(Conv2d Operators/src/Conv2D.cpp)
add_library(BatchNorm Operators/src/batchnorm.cpp)
add_library(Utils utilities/src/utils.cpp)
add_library(UtilsTest utilities/src/test.cpp)
add_library(MaxPooling Operators/src/maxpooling.cpp)
add_library(Dense Operators/src/dense.cpp)
add_library(TestOperators Test_Operators/src/unit_test.cpp)
add_library(Relu Operators/src/relu.cpp)

target_include_directories(Conv2d PUBLIC Operators/include)
target_include_directories(Utils PUBLIC utilities/include)
target_include_directories(UtilsTest PUBLIC utilities/include)
target_include_directories(BatchNorm PUBLIC Operators/include)
target_include_directories(MaxPooling PUBLIC Operators/include)
target_include_directories(Dense PUBLIC Operators/include)
target_include_directories(TestOperators PUBLIC Test_Operators/include)
target_include_directories(Relu PUBLIC Operators/include)

add_executable(main src/main.cpp)
target_link_libraries(main PUBLIC  Dense TestOperators UtilsTest Conv2d Utils BatchNorm MaxPooling PRIVATE nlohmann_json::nlohmann_json TestOperators ${OpenCV_LIBS})