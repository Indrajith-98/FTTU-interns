# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.16)

# Set the project name and version
project(CIFAR10_CPP VERSION 1.0 LANGUAGES CXX)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)

set(OpenCV_DIR /opt/homebrew/)

include_directories(
    /Users/pravinpb/homebrew/Open_CV/opencv/include/
    /opt/homebrew/opt/opencv
    /System/Volumes/Data/Users/pravinpb/vcpkg/installed/arm64-osx/include
    /Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/imageManipulation/Functions/include
)

set(SRCS
    /Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/imageManipulation/Functions/src/adjust_contrast.cpp
    /Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/imageManipulation/Functions/src/adjust_highlights.cpp
    /Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/imageManipulation/Functions/src/adjust_saturation.cpp
    /Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/imageManipulation/Functions/src/adjust_shadows.cpp
    /Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/imageManipulation/Functions/src/convert_bgr_to_hsv.cpp
    /Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/imageManipulation/src/main.cpp
    
)

# Create an executable
add_executable(compiled ${SRCS})

# Link OpenCV libraries
find_package(OpenCV REQUIRED)
target_link_libraries(compiled ${OpenCV_LIBS})

# Specify additional compiler flags
target_compile_options(compiled PRIVATE -target arm64-apple-macos)