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
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\7501\Testing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\7501\Testing\build

# Include any dependencies generated for this target.
include CMakeFiles/MyMath.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyMath.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyMath.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyMath.dir/flags.make

CMakeFiles/MyMath.dir/codegen:
.PHONY : CMakeFiles/MyMath.dir/codegen

CMakeFiles/MyMath.dir/src/my_math.cpp.obj: CMakeFiles/MyMath.dir/flags.make
CMakeFiles/MyMath.dir/src/my_math.cpp.obj: CMakeFiles/MyMath.dir/includes_CXX.rsp
CMakeFiles/MyMath.dir/src/my_math.cpp.obj: C:/Users/7501/Testing/src/my_math.cpp
CMakeFiles/MyMath.dir/src/my_math.cpp.obj: CMakeFiles/MyMath.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\7501\Testing\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyMath.dir/src/my_math.cpp.obj"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyMath.dir/src/my_math.cpp.obj -MF CMakeFiles\MyMath.dir\src\my_math.cpp.obj.d -o CMakeFiles\MyMath.dir\src\my_math.cpp.obj -c C:\Users\7501\Testing\src\my_math.cpp

CMakeFiles/MyMath.dir/src/my_math.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyMath.dir/src/my_math.cpp.i"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\7501\Testing\src\my_math.cpp > CMakeFiles\MyMath.dir\src\my_math.cpp.i

CMakeFiles/MyMath.dir/src/my_math.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyMath.dir/src/my_math.cpp.s"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\7501\Testing\src\my_math.cpp -o CMakeFiles\MyMath.dir\src\my_math.cpp.s

# Object files for target MyMath
MyMath_OBJECTS = \
"CMakeFiles/MyMath.dir/src/my_math.cpp.obj"

# External object files for target MyMath
MyMath_EXTERNAL_OBJECTS =

libMyMath.a: CMakeFiles/MyMath.dir/src/my_math.cpp.obj
libMyMath.a: CMakeFiles/MyMath.dir/build.make
libMyMath.a: CMakeFiles/MyMath.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\7501\Testing\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libMyMath.a"
	$(CMAKE_COMMAND) -P CMakeFiles\MyMath.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\MyMath.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyMath.dir/build: libMyMath.a
.PHONY : CMakeFiles/MyMath.dir/build

CMakeFiles/MyMath.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\MyMath.dir\cmake_clean.cmake
.PHONY : CMakeFiles/MyMath.dir/clean

CMakeFiles/MyMath.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\7501\Testing C:\Users\7501\Testing C:\Users\7501\Testing\build C:\Users\7501\Testing\build C:\Users\7501\Testing\build\CMakeFiles\MyMath.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/MyMath.dir/depend

