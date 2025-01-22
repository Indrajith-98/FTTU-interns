cmake_minimum_required(VERSION 3.10)

project(Image_Preprocessing_Assignment)

set(OpenCV_DIR "C:/opencv/build")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output)

find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
