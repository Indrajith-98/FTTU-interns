# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/prasa/OneDrive/Desktop/gtest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build

# Include any dependencies generated for this target.
include Assignment_3/CMakeFiles/assignment_3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Assignment_3/CMakeFiles/assignment_3.dir/compiler_depend.make

# Include the progress variables for this target.
include Assignment_3/CMakeFiles/assignment_3.dir/progress.make

# Include the compile flags for this target's objects.
include Assignment_3/CMakeFiles/assignment_3.dir/flags.make

Assignment_3/CMakeFiles/assignment_3.dir/assignment_3.cpp.o: Assignment_3/CMakeFiles/assignment_3.dir/flags.make
Assignment_3/CMakeFiles/assignment_3.dir/assignment_3.cpp.o: /mnt/c/Users/prasa/OneDrive/Desktop/gtest/Assignment_3/assignment_3.cpp
Assignment_3/CMakeFiles/assignment_3.dir/assignment_3.cpp.o: Assignment_3/CMakeFiles/assignment_3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Assignment_3/CMakeFiles/assignment_3.dir/assignment_3.cpp.o"
	cd /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/Assignment_3 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Assignment_3/CMakeFiles/assignment_3.dir/assignment_3.cpp.o -MF CMakeFiles/assignment_3.dir/assignment_3.cpp.o.d -o CMakeFiles/assignment_3.dir/assignment_3.cpp.o -c /mnt/c/Users/prasa/OneDrive/Desktop/gtest/Assignment_3/assignment_3.cpp

Assignment_3/CMakeFiles/assignment_3.dir/assignment_3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/assignment_3.dir/assignment_3.cpp.i"
	cd /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/Assignment_3 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/prasa/OneDrive/Desktop/gtest/Assignment_3/assignment_3.cpp > CMakeFiles/assignment_3.dir/assignment_3.cpp.i

Assignment_3/CMakeFiles/assignment_3.dir/assignment_3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/assignment_3.dir/assignment_3.cpp.s"
	cd /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/Assignment_3 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/prasa/OneDrive/Desktop/gtest/Assignment_3/assignment_3.cpp -o CMakeFiles/assignment_3.dir/assignment_3.cpp.s

Assignment_3/CMakeFiles/assignment_3.dir/fibonacci.cpp.o: Assignment_3/CMakeFiles/assignment_3.dir/flags.make
Assignment_3/CMakeFiles/assignment_3.dir/fibonacci.cpp.o: /mnt/c/Users/prasa/OneDrive/Desktop/gtest/Assignment_3/fibonacci.cpp
Assignment_3/CMakeFiles/assignment_3.dir/fibonacci.cpp.o: Assignment_3/CMakeFiles/assignment_3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Assignment_3/CMakeFiles/assignment_3.dir/fibonacci.cpp.o"
	cd /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/Assignment_3 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Assignment_3/CMakeFiles/assignment_3.dir/fibonacci.cpp.o -MF CMakeFiles/assignment_3.dir/fibonacci.cpp.o.d -o CMakeFiles/assignment_3.dir/fibonacci.cpp.o -c /mnt/c/Users/prasa/OneDrive/Desktop/gtest/Assignment_3/fibonacci.cpp

Assignment_3/CMakeFiles/assignment_3.dir/fibonacci.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/assignment_3.dir/fibonacci.cpp.i"
	cd /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/Assignment_3 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/prasa/OneDrive/Desktop/gtest/Assignment_3/fibonacci.cpp > CMakeFiles/assignment_3.dir/fibonacci.cpp.i

Assignment_3/CMakeFiles/assignment_3.dir/fibonacci.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/assignment_3.dir/fibonacci.cpp.s"
	cd /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/Assignment_3 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/prasa/OneDrive/Desktop/gtest/Assignment_3/fibonacci.cpp -o CMakeFiles/assignment_3.dir/fibonacci.cpp.s

# Object files for target assignment_3
assignment_3_OBJECTS = \
"CMakeFiles/assignment_3.dir/assignment_3.cpp.o" \
"CMakeFiles/assignment_3.dir/fibonacci.cpp.o"

# External object files for target assignment_3
assignment_3_EXTERNAL_OBJECTS =

Assignment_3/assignment_3: Assignment_3/CMakeFiles/assignment_3.dir/assignment_3.cpp.o
Assignment_3/assignment_3: Assignment_3/CMakeFiles/assignment_3.dir/fibonacci.cpp.o
Assignment_3/assignment_3: Assignment_3/CMakeFiles/assignment_3.dir/build.make
Assignment_3/assignment_3: Assignment_3/libfibonacci.a
Assignment_3/assignment_3: Assignment_3/CMakeFiles/assignment_3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable assignment_3"
	cd /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/Assignment_3 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/assignment_3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Assignment_3/CMakeFiles/assignment_3.dir/build: Assignment_3/assignment_3
.PHONY : Assignment_3/CMakeFiles/assignment_3.dir/build

Assignment_3/CMakeFiles/assignment_3.dir/clean:
	cd /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/Assignment_3 && $(CMAKE_COMMAND) -P CMakeFiles/assignment_3.dir/cmake_clean.cmake
.PHONY : Assignment_3/CMakeFiles/assignment_3.dir/clean

Assignment_3/CMakeFiles/assignment_3.dir/depend:
	cd /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/prasa/OneDrive/Desktop/gtest /mnt/c/Users/prasa/OneDrive/Desktop/gtest/Assignment_3 /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/Assignment_3 /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/Assignment_3/CMakeFiles/assignment_3.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : Assignment_3/CMakeFiles/assignment_3.dir/depend

