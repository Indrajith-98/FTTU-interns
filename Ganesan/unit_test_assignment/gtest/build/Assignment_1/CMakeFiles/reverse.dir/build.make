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
include Assignment_1/CMakeFiles/reverse.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Assignment_1/CMakeFiles/reverse.dir/compiler_depend.make

# Include the progress variables for this target.
include Assignment_1/CMakeFiles/reverse.dir/progress.make

# Include the compile flags for this target's objects.
include Assignment_1/CMakeFiles/reverse.dir/flags.make

Assignment_1/CMakeFiles/reverse.dir/reverse.cpp.o: Assignment_1/CMakeFiles/reverse.dir/flags.make
Assignment_1/CMakeFiles/reverse.dir/reverse.cpp.o: /mnt/c/Users/prasa/OneDrive/Desktop/gtest/Assignment_1/reverse.cpp
Assignment_1/CMakeFiles/reverse.dir/reverse.cpp.o: Assignment_1/CMakeFiles/reverse.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Assignment_1/CMakeFiles/reverse.dir/reverse.cpp.o"
	cd /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/Assignment_1 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Assignment_1/CMakeFiles/reverse.dir/reverse.cpp.o -MF CMakeFiles/reverse.dir/reverse.cpp.o.d -o CMakeFiles/reverse.dir/reverse.cpp.o -c /mnt/c/Users/prasa/OneDrive/Desktop/gtest/Assignment_1/reverse.cpp

Assignment_1/CMakeFiles/reverse.dir/reverse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/reverse.dir/reverse.cpp.i"
	cd /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/Assignment_1 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/prasa/OneDrive/Desktop/gtest/Assignment_1/reverse.cpp > CMakeFiles/reverse.dir/reverse.cpp.i

Assignment_1/CMakeFiles/reverse.dir/reverse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/reverse.dir/reverse.cpp.s"
	cd /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/Assignment_1 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/prasa/OneDrive/Desktop/gtest/Assignment_1/reverse.cpp -o CMakeFiles/reverse.dir/reverse.cpp.s

# Object files for target reverse
reverse_OBJECTS = \
"CMakeFiles/reverse.dir/reverse.cpp.o"

# External object files for target reverse
reverse_EXTERNAL_OBJECTS =

Assignment_1/libreverse.a: Assignment_1/CMakeFiles/reverse.dir/reverse.cpp.o
Assignment_1/libreverse.a: Assignment_1/CMakeFiles/reverse.dir/build.make
Assignment_1/libreverse.a: Assignment_1/CMakeFiles/reverse.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libreverse.a"
	cd /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/Assignment_1 && $(CMAKE_COMMAND) -P CMakeFiles/reverse.dir/cmake_clean_target.cmake
	cd /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/Assignment_1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/reverse.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Assignment_1/CMakeFiles/reverse.dir/build: Assignment_1/libreverse.a
.PHONY : Assignment_1/CMakeFiles/reverse.dir/build

Assignment_1/CMakeFiles/reverse.dir/clean:
	cd /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/Assignment_1 && $(CMAKE_COMMAND) -P CMakeFiles/reverse.dir/cmake_clean.cmake
.PHONY : Assignment_1/CMakeFiles/reverse.dir/clean

Assignment_1/CMakeFiles/reverse.dir/depend:
	cd /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/prasa/OneDrive/Desktop/gtest /mnt/c/Users/prasa/OneDrive/Desktop/gtest/Assignment_1 /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/Assignment_1 /mnt/c/Users/prasa/OneDrive/Desktop/gtest/build/Assignment_1/CMakeFiles/reverse.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : Assignment_1/CMakeFiles/reverse.dir/depend

