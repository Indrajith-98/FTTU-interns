# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.16)

# Set the project name and version
project(CIFAR10_CPP VERSION 1.0 LANGUAGES CXX)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)

include_directories(
    /opt/homebrew/include/opencv4
    /System/Volumes/Data/Users/pravinpb/vcpkg/installed/arm64-osx/include
    /Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/timeApp/Functions/include
)

set(SRCS
    /Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/timeApp/Functions/src/get_current_time.cpp
    /Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/timeApp/Functions/src/alarm.cpp
    /Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/timeApp/Functions/src/stopwatch.cpp
    /Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/timeApp/Functions/src/time_difference.cpp
    /Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/timeApp/Functions/src/timer.cpp
    /Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/timeApp/src/main.cpp
)

# Create an executable
add_executable(compiled ${SRCS})

# Link OpenCV libraries
find_package(OpenCV REQUIRED)
target_link_libraries(compiled ${OpenCV_LIBS})

# Specify additional compiler flags
target_compile_options(compiled PRIVATE -target arm64-apple-macos)