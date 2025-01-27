# Neural Network Implementation in C++

## Overview
This project demonstrates the implementation of a flexible neural network pipeline in C++ designed for processing data through convolutional, max pooling, batch normalization, and dense layers. The system utilizes pre-configured layers, weights, and biases stored in binary files, enabling efficient and portable model processing. A JSON configuration file allows for dynamic and reusable setup of layer parameters and file paths.

## Key Features

### 1. **Dynamic Configuration Loading**
   - Layer configurations (weights, biases, input paths) are read from a JSON file.
   - This approach minimizes hardcoding and simplifies updates to model structures or paths.

### 2. **Binary File Handling**
   - Efficient memory use and portability via input data, weights, and biases stored in binary format.
   - Utility functions are implemented for reading and processing these binary files.

### 3. **Custom Neural Network Layers**
   - **Convolutional Layers** with ReLU activation and configurable padding.
   - **MaxPooling Layers** for dimensionality reduction.
   - **Dense Layers** with ReLU and Softmax activation functions.

### 4. **Intermediate Layer Output Visualization**
   - TensorFlow/Keras utilities are used to visualize intermediate outputs from all layers.
   - Specifically designed to print the first channel of multi-dimensional outputs for easier debugging.

### 5. **End-to-End Implementation**
   - A complete pipeline from low-level neural network operations (e.g., convolutions, dense) to high-level model evaluation with TensorFlow/Keras.
   - Visualizes transformations at each layer for model inspection and analysis.

### 6. **Unit Testing**
   - Unit tests validate the functionality of each implemented module.
   - Ensures that individual components such as convolutions, pooling, and dense layers work as expected.

## Project Folder Structure
- `operators/` : Contains source code and .h files for the deep learning operators and layers.
- `src/` : Contains the main.cpp file.
- `include/` : Header files defining interfaces and structures for layers and utilities.
- `report/` : Contains Unit Test outputs.
- `data/` : weights are extracted from .h5 model.
- `CMakeLists.txt` : Configuration file for building the project with CMake.
- `README.txt` : This documentation file.

## System Requirements
- **Operating System**: Windows
- **Compiler**: GCC 9.4.0 or higher
- **Build System**: CMake 3.16+ or higher
- **Dependencies**:
  - C++17 Standard Library
  - TensorFlow/Keras (for intermediate output visualization)

## How to Use

### 1. **Configure JSON File**
   - Provide a configuration file (`HyperParameterConfigurationFile.json`) specifying the paths for weights, biases, and input data.

### 2. **Compile and Run the C++ Code**
   - Use CMake to build the project:  
     `mkdir build`
     `cd build`
     `cmake ..`
     `cmake --build .`
     `cd Debug`
     `cd .\Filename.exe`  
   - replace Filename.exe with the file that are generated during cmake runtime.
   - After compilation, run the generated executable to process the input data and obtain classification results.

### 3. **Unit Testing**
   - Unit tests are provided in the `report/` folder to validate each layer's operation. Run the tests to ensure correctness.

## Applications
- Custom neural network implementation suited for environments with limited support for high-level libraries.
- Useful for debugging and visualizing the transformations in a neural network layer-by-layer.
- Flexible for deploying pre-trained models with custom input/output setups.
