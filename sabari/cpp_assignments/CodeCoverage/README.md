# C++ Code Coverage with GTest

This repository demonstrates how to use Google Test (GTest) to test C++ code and generate code coverage reports using OpenCppCoverage.

## Overview

This project focuses on testing the functionality provided in the `my_math` library. The core logic of the `my_math` library is located in `@my_math.cpp`. The tests are implemented using GTest and can be found in `@Tests/test.cpp`. The project also includes a precompiled header file `@Tests/pch.h`.

## Testing Framework

- **Google Test (GTest):** A C++ testing framework used to write and execute unit tests.
- **OpenCppCoverage:** A tool used to generate code coverage reports.

## Code Structure

- `my_math/my_math.cpp`: Contains the implementation of the mathematical functions being tested.
- `Tests/test.cpp`: Contains the unit tests for the functions in `my_math.cpp`.
- `Tests/pch.h`: Precompiled header file used in the test project.

## Code Coverage

The code coverage report is generated using OpenCppCoverage. The following command was used to generate the report:

```bash
OpenCppCoverage --sources my_math\my_math.cpp -- x64\debug\Tests.exe
```

This command specifies that coverage should be collected for the source files in `my_math\my_math.cpp` when running the test executable `x64\debug\Tests.exe`.
