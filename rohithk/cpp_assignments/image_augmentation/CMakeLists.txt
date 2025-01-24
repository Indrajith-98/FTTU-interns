cmake_minimum_required(VERSION 3.28.3)

project( OpenCV_learn )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} include )

add_library(ImageProcessor src/image_processor.cpp)

add_executable( second second.cpp )

target_include_directories(ImageProcessor PUBLIC include)

target_link_libraries( second PRIVATE ImageProcessor ${OpenCV_LIBS} )

