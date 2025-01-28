### About
This project uses a CNN based (3 convolution + 2 dense) trained tensorflow model on cifar-10 dataset to test a image through layer-by-layer execution in C++. Model Layers attributes like weights, filters, kernel sizes are extracted and used in custom C++ implementations of each layer. During execution, intermediate outputs and details such as layer names and time taken for execution of each layer are logged. Outputs from the custom implementation are compared with the Python keras model to ensure the correct prediction.<br> [Tensorflow model for cifar 10 dataset using python (Ass 1) ](https://github.com/deivanayakis/CIFAR10-IMAGE-CLASSIFICATION)

### Project Folder Structure

```
DLOPL/
├── configs/
│   └── json/
│       └── model_config_details.json
│
├── data/
│   ├── input/
│   │   └── truck.json
│   ├── output/
│   │   └── intermediate_result_for_truck.json
│   └── reference/
│       └── model_result_for_truck.json
│
├── extern/
│   └── json.hpp
│
├── Operators/
│   ├── src/
│   │   ├── conv.cpp
│   │   └── prelu.cpp
│   └── include/
│       ├── conv.h
│       └── prelu.h
│
├── Test_Operators/
│   ├── src/
│   │   ├── conv_test.cpp
│   │   └── prelu_test.cpp
│   └── include/
│       ├── conv_test.h
│       └── prelu_test.h
│
├── utils/
│   ├── include/
│   │   ├── Fileutils.h
│   │   └── Logutils.h
│   └── src/
│       ├── Fileutils.cpp
│       └── Logutils.cpp
│
├── Reports/
│   ├── execution.log
│   ├── dualTestExecution.log
│   └── predictions.json
│
|__ build/
|
├── .gitignore
├── main.cpp
├── CMakeLists.txt
└── README.md
```

### OS and Tools used

Operating System : Windows 11 <br>
Version : 23H2 <br>
Architecture : 64 <br>

IDE : Visual Studio Code (1.96.2) <br>
Build System : CMake (3.31.3) <br>
Compiler : MinGW (14.2.0) <br>
Library : nlohmann/json (3.11.3) <br>
Version Control : Git (2.42.0.windows.2) <br>

### Run the project

Clone this repository
```
git clone https://github.com/deivanayakis/DL_Operators_Layers.git
cd DL_Operators_Layers
```
Create Build Directory
```
mkdir build
cd build
```
Run CMake and executable
```
cmake ..
cmake --build .
./dlopl.exe
```

### How to Interpret the Results

- **Intermediate Layer Outputs**:  
  Check the `data/output` directory for results from each layer for the tested image.

- **Dual Test Results**:  
  View the `Reports/dualTestResult.log` for comparisons between unit and model test outputs.

- **Execution Time**:  
  The `Reports/execution.log` file shows how long each layer took to process.

- **Predictions**:  
  The `Reports/predictions.json` file contains the model's final predictions for the input image.




