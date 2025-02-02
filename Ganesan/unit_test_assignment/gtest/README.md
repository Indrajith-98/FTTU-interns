# Unit Test Assignment - CMake Project with Google Test

## Overview
This project demonstrates how to set up unit tests using CMake and Google Test. The project is divided into three sub-projects: **Assignment_1**, **Assignment_2**, and **Assignment_3**. Google Test is used for writing and running unit tests in C++.

### CMake Configuration
The CMake configuration is set up to download and integrate Google Test (GTest) as an external dependency using `FetchContent`. This allows the project to be built on any system with minimal setup.

## Features
1. **CMake Setup**: 
   - Minimum required version of CMake is `3.10`.
   - Google Test is downloaded using `FetchContent` for automatic integration.
   - The project is configured to use C++11 for compilation.

2. **Sub-Projects**:
   - The project consists of three sub-projects:
     - `Assignment_1`: Unit tests for the first assignment.
     - `Assignment_2`: Unit tests for the second assignment.
     - `Assignment_3`: Unit tests for the third assignment.

3. **Google Test Integration**:
   - Google Test is fetched directly from the GitHub repository using `FetchContent_Declare`.
   - Unit tests are written using the Google Test framework.

4. **Cross-Platform Compatibility**:
   - The project setup is cross-platform and works on both Windows and Linux/macOS. For Windows users, the shared CRT is enabled with `gtest_force_shared_crt ON`.

5. **CTest Integration**:
   - CTest is included to enable running the tests with the `ctest` command, which simplifies the testing process.

## Requirements
- **CMake 3.10 or higher**: Required to build the project and manage dependencies.
- **Google Test**: Automatically downloaded via CMake.

