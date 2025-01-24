# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(I_P_A)

# Define the OpenCV directory where OpenCV is installed
set(OpenCV_DIR "C:/Users/sendm/Downloads/opencv/build/x64/vc16/lib")  # Update the OpenCV directory path if necessary
set(OpenCV_INCLUDE_DIRS "C:/Users/sendm/Downloads/opencv/build/include")
set(OpenCV_LIBS "opencv_calib3d;opencv_core;opencv_dnn;opencv_features2d;opencv_flann;opencv_gapi;opencv_highgui;opencv_imgcodecs;opencv_imgproc;opencv_ml;opencv_objdetect;opencv_photo;opencv_stitching;opencv_video;opencv_videoio;opencv_world")

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)

# Find the OpenCV package
find_package(OpenCV REQUIRED)

# Check if OpenCV was found
if (NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found!")
else()
    message(STATUS "OpenCV found!")
endif()

# Include OpenCV header files
include_directories(${OpenCV_INCLUDE_DIRS})

# Add your executable (main.cpp file located in the root folder)
add_executable(I_P_A main.cpp)

# Link the OpenCV libraries to your project
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_link_libraries(I_P_A ${OpenCV_LIBS})
target_link_libraries(I_P_A
    opencv_core
    opencv_imgcodecs
    opencv_highgui
    opencv_imgproc
)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OBJECT_PATH_MAX 500)

# Specify the compiler (adjust paths if necessary)
set(CMAKE_C_COMPILER "C:/Program Files/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/Program Files/mingw64/bin/g++.exe")
set(CMAKE_PREFIX_PATH "C:/Users/sendm/Downloads/opencv/build/x64/vc16/lib")




# Print OpenCV library and include directories
message(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")
message(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")

# Optional: If you are using any custom library paths, you can specify them here:
# link_directories("C:/path/to/your/libs")
# include_directories("C:/path/to/your/includes")
