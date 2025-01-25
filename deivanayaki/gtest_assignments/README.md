# GoogleTEST and Code Coverage

### About

A test suite for each function in src/my_math.cpp was written using Google Test (gtest), and code coverage was enhanced with LCOV and GCOV.

### Run the Program

##### Create build directory

```
mkdir build
cd build
```

##### Build and Run

```
cmake ..
cmake --build .
./AllTests.exe
```

This creates the .gcda, .gcno, .gcvo files (build/CMakeFiles/MathLib.dir/src/) which can be used to generate code coverage reports.

### Code Coverage

#### GCOV

```
gcov CMakeFiles/MathLib.dir/src/my_math.cpp.
```

#### LCOV

```
cd CMakeFiles/MathLib.dir/src

lcov --capture --directory . --output-file coverage.info

genhtml coverage.info --output-directory out

cd out

explorer index.html

```

