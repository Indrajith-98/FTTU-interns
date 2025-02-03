# Creating C++ piplines for the CIFAR 10 Trained Resnet Python model

This project contains a pretrained Resnet model with CIFAR 10 which contains 3 convolution layers, 1 flatten layer annd 2 dense layer so totally 6 layers.  This project aims to write the C++ piplines for these layers and makes the model to predict the output and test with respect to the python model execution.

---

## About

The core objectives of this project are:

1. **Model Execution**:
   - The TensorFlow model trained on the CIFAR-10 dataset is executed layer-by-layer in C++.
   - Model attributes such as channels, units, weights, filters, kernel sizes, and biases are extracted from the TensorFlow model and utilized in custom C++ implementations.

2. **Logging Intermediate Outputs**:
   - Intermediate outputs, layer names, and details are logged during execution for analysis.

3. **Validation**:
   - The outputs from the custom C++ implementation are compared with the Python Keras model outputs to ensure the correctness of predictions.

---

## OS and Tools Used

- **Operating System**: Windows 11  
  - **Version**: 23H2  
  - **Architecture**: 64-bit  

- **IDE**: Visual Studio Code (1.96.2)  
- **Build System**: CMake (3.28.3)  
- **Compiler**: MinGW (13.3.0)  
- **Library**: nlohmann/json (3.11.3)  
- **Version Control**: Git (2.43.0)  

---

## Project directory structure



├── README.md                # Project documentation

├──configs                   # Directory containing a config json file having the details for each layers

|    └──json

|    |   └── model_configuration.json     

├── Data                     # Directory containing input and output data

│   ├── input                # Subdirectory for input files (e.g., test images)

│   ├── ref_output           # Subdirectory for attributes of each layer for a particular image

|   ├── weights              # Subdirectory for weights files of each layer

|   └── output               # Subdirectory for storing layer-by-layer output logs

├── Operators

|   ├── include                  # Header of the various layers

|   |   ├──conv2d.h

|   |   ├──dense.h

|   |   ├──flatten.h

|   |   ├──max_pooling.h

|   |   ├──relu.h

|   |   ├──relu.h

|   ├── src                      # Implemetation of layers used in the project

|   |   ├──conv2d.cpp

|   |   ├──dense.cpp

|   |   ├──flatten.cpp

|   |   ├──max_pooling.cpp

|   |   ├──relu.cpp

|   |   ├──softmax.cpp  

├── Reports                  # Directory containing result comparisons and there are also layer wise output wise results

│   ├── execution_log        # Directory contains the execution_log.txt

│   ├── output               # Contains the each layer output in C++

│   └── result.txt          # Text file with overall test and comparison results

├── src                      # Contains the main.cpp

├── Test Operators

|  ├── include                  # Header of the functions used during testing various layers

|      testing.h

|  ├── src                      # Implemetation of functions and testing the layers used in the project

|     └──testing.cpp  


├── Operators

|   ├── include                  # Header of the various utility functions

|   |   ├──file_io.h

|   |   ├──load_json.h

|   |   ├──logging.h

|   |   ├──prediction.h


|   ├── src                      # Implemetation of utility functions used in this project

|   |   ├──file_io.cpp

|   |   ├──load_json.cpp

|   |   ├──logging.cpp

|   |   ├──prediction.cpp
          



## Run the Project


## Create build directory

```bash
mkdir build
cd build

```

## Run CMake and executables

```bash
cmake ..
make
./deeplearningoperators.exe

```

## How to interpret the results:

- Intermediate layer outputs
  Check the Report/output directory for results from each layer for the tested image
- Dual test results
  View the Reports/result.txt file for comparisons between the unit and model test outputs and also the final predictions for the input image.

```