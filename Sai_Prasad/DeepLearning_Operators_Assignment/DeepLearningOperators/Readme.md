# CIFAR-10 C++ Model Execution

This project showcases the execution of a Convolutional Neural Network (CNN) model built with TensorFlow, consisting of 3 convolutional layers followed by 2 fully connected layers, trained on the CIFAR-10 dataset. The model is implemented in C++ to allow for step-by-step layer execution, providing a custom solution that ensures that is validated the outputs against the original Keras model in Python.

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

- **Operating System**: WSL (Windows Subsystem for Linux), Ubuntu
- **IDE**: Visual Studio Code (1.96.4gcc)  
- **Build System**: CMake (3.28.3)  
- **Compiler**: MinGW (13.3.0)  
- **Library**: nlohmann/json (3.11.3)  
- **Version Control**: Git (2.47.1)  

---

## Project directory structure

CIFAR-10-cpp

├── README.md                # Project documentation

├── src 

    └──main.cpp                # main program

├── Configs                   # Directory containing a config json file having the details for each layers

    └── json

       └── model_configuration.json     

├── data                     # Directory containing input and output data

   ├── inputs                # Subdirectory for input files (e.g., test images)

   ├── ref_output_           # Subdirectory for reference outputs of each layer

   ├── weights              # Subdirectory for weights files of each layer

   └── outputs               # Subdirectory for storing layer-by-layer output logs

├── Operators

   ├── include                  # Header of the various layers

      ├──conv2d.h

      ├──dense.h

      ├──flatten.h

      ├──max_pooling2d.h

      └──softmax.h

      └──relu.h

   ├── src                      # Implemetation of layers used in the project

      ├──conv2d.cpp

      ├──dense.cpp

      ├──flatten.cpp

      ├──max_pooling2d.cpp

      └──softmax.cpp

      └──relu.cpp  

├── Test Operators

  ├── include                  # Header of the functions used during testing various layers

      └──testing.h

  ├── src                      # Implemetation of functions and testing the layers used in the project

     └──testing.cpp  

├── Report                  # Directory containing result comparisons and there are also layer wise output wise results

   └── results.txt          # Text file with overall test and comparison results

   └── execution_log.txt    # contains execution log of each layer

   └── output               # contains output of each layer for comparison

├── utilties                # Directory for header files for the project

    ├── include                  # Header of the most used functions in the project

       └──file_io.h

       └──load_json.h

       └──logging.h

       └──prediction.h

    ├── src                      # Implemetation of most used functions in the project

       └──file_io.cpp

       └──load_json.cpp

       └──logging.cpp

       └──prediction.cpp               

├── CMakeLists.txt               # CMake build for the project compilation

## Run the Project in WSL (Ubuntu)


## Create build directory

```bash
mkdir build
cd build

```

## Run CMake and executables

```bash
cmake ..
make
./DeepLearningOperators.exe

```

## How to interpret the results:

- Intermediate layer outputs
  Check the Report/output directory for results from each layer for the tested image
- Dual test results
  View the Report/results.txt file for comparisons between the unit and model test outputs and also the final predictions for the input image.

```