# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = F:\cmake\bin\cmake.exe

# The command to remove a file.
RM = F:\cmake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "F:\MCW\training assignments\gtest_assignments"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "F:\MCW\training assignments\gtest_assignments\build"

# Include any dependencies generated for this target.
include CMakeFiles/edge_case_tests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/edge_case_tests.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/edge_case_tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/edge_case_tests.dir/flags.make

CMakeFiles/edge_case_tests.dir/codegen:
.PHONY : CMakeFiles/edge_case_tests.dir/codegen

CMakeFiles/edge_case_tests.dir/test_coverage/edge_case_tests.cpp.obj: CMakeFiles/edge_case_tests.dir/flags.make
CMakeFiles/edge_case_tests.dir/test_coverage/edge_case_tests.cpp.obj: CMakeFiles/edge_case_tests.dir/includes_CXX.rsp
CMakeFiles/edge_case_tests.dir/test_coverage/edge_case_tests.cpp.obj: F:/MCW/training\ assignments/gtest_assignments/test_coverage/edge_case_tests.cpp
CMakeFiles/edge_case_tests.dir/test_coverage/edge_case_tests.cpp.obj: CMakeFiles/edge_case_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="F:\MCW\training assignments\gtest_assignments\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/edge_case_tests.dir/test_coverage/edge_case_tests.cpp.obj"
	"F:\code blocks\CodeBlocks\MinGW\bin\c++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/edge_case_tests.dir/test_coverage/edge_case_tests.cpp.obj -MF CMakeFiles\edge_case_tests.dir\test_coverage\edge_case_tests.cpp.obj.d -o CMakeFiles\edge_case_tests.dir\test_coverage\edge_case_tests.cpp.obj -c "F:\MCW\training assignments\gtest_assignments\test_coverage\edge_case_tests.cpp"

CMakeFiles/edge_case_tests.dir/test_coverage/edge_case_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/edge_case_tests.dir/test_coverage/edge_case_tests.cpp.i"
	"F:\code blocks\CodeBlocks\MinGW\bin\c++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "F:\MCW\training assignments\gtest_assignments\test_coverage\edge_case_tests.cpp" > CMakeFiles\edge_case_tests.dir\test_coverage\edge_case_tests.cpp.i

CMakeFiles/edge_case_tests.dir/test_coverage/edge_case_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/edge_case_tests.dir/test_coverage/edge_case_tests.cpp.s"
	"F:\code blocks\CodeBlocks\MinGW\bin\c++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "F:\MCW\training assignments\gtest_assignments\test_coverage\edge_case_tests.cpp" -o CMakeFiles\edge_case_tests.dir\test_coverage\edge_case_tests.cpp.s

# Object files for target edge_case_tests
edge_case_tests_OBJECTS = \
"CMakeFiles/edge_case_tests.dir/test_coverage/edge_case_tests.cpp.obj"

# External object files for target edge_case_tests
edge_case_tests_EXTERNAL_OBJECTS =

edge_case_tests.exe: CMakeFiles/edge_case_tests.dir/test_coverage/edge_case_tests.cpp.obj
edge_case_tests.exe: CMakeFiles/edge_case_tests.dir/build.make
edge_case_tests.exe: libmath_lib.a
edge_case_tests.exe: lib/libgtest.a
edge_case_tests.exe: lib/libgtest_main.a
edge_case_tests.exe: lib/libgtest.a
edge_case_tests.exe: CMakeFiles/edge_case_tests.dir/linkLibs.rsp
edge_case_tests.exe: CMakeFiles/edge_case_tests.dir/objects1.rsp
edge_case_tests.exe: CMakeFiles/edge_case_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="F:\MCW\training assignments\gtest_assignments\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable edge_case_tests.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\edge_case_tests.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/edge_case_tests.dir/build: edge_case_tests.exe
.PHONY : CMakeFiles/edge_case_tests.dir/build

CMakeFiles/edge_case_tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\edge_case_tests.dir\cmake_clean.cmake
.PHONY : CMakeFiles/edge_case_tests.dir/clean

CMakeFiles/edge_case_tests.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "F:\MCW\training assignments\gtest_assignments" "F:\MCW\training assignments\gtest_assignments" "F:\MCW\training assignments\gtest_assignments\build" "F:\MCW\training assignments\gtest_assignments\build" "F:\MCW\training assignments\gtest_assignments\build\CMakeFiles\edge_case_tests.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/edge_case_tests.dir/depend

