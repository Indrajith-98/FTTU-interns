cmake_minimum_required(VERSION 3.10...3.26)
project(ImageProcessing VERSION 0.1.0)

# Enable testing
include(CTest)
enable_testing()

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include OpenCV directories
include_directories(${OpenCV_INCLUDE_DIRS})

# Add executable target
add_executable(ImageProcessing main.cpp)

# Link OpenCV libraries
target_link_libraries(ImageProcessing ${OpenCV_LIBS})

# Set CPack properties for packaging
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)