﻿# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\ImageProcessing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\ImageProcessing\build

# Utility rule file for ContinuousMemCheck.

# Include any custom commands dependencies for this target.
include CMakeFiles\ContinuousMemCheck.dir\compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles\ContinuousMemCheck.dir\progress.make

CMakeFiles\ContinuousMemCheck:
	echo >nul && "C:\Program Files\CMake\bin\ctest.exe" -D ContinuousMemCheck

CMakeFiles\ContinuousMemCheck.dir\codegen:
.PHONY : CMakeFiles\ContinuousMemCheck.dir\codegen

ContinuousMemCheck: CMakeFiles\ContinuousMemCheck
ContinuousMemCheck: CMakeFiles\ContinuousMemCheck.dir\build.make
.PHONY : ContinuousMemCheck

# Rule to build all files generated by this target.
CMakeFiles\ContinuousMemCheck.dir\build: ContinuousMemCheck
.PHONY : CMakeFiles\ContinuousMemCheck.dir\build

CMakeFiles\ContinuousMemCheck.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ContinuousMemCheck.dir\cmake_clean.cmake
.PHONY : CMakeFiles\ContinuousMemCheck.dir\clean

CMakeFiles\ContinuousMemCheck.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\ImageProcessing D:\ImageProcessing D:\ImageProcessing\build D:\ImageProcessing\build D:\ImageProcessing\build\CMakeFiles\ContinuousMemCheck.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles\ContinuousMemCheck.dir\depend

