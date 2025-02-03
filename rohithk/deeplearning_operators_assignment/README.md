# CIFAR10_CPP  

## Deep Learning Layers and Operators in C++  

### Project Overview  
This project focuses on developing a C++ application to handle deep learning model layers such as Convolutional, ReLU, Softmax, and more. The objective is to implement the fundamental operations of these layers, including input processing, computations, and output generation. The application will read configuration files, execute layer operations, and validate functionality through testing.  

### Project Directory Structure  

#### **operators**  
Contains the C++ implementations of essential operators like Convolution and Batch Normalization. These functions execute layer-specific operations, such as element-wise addition in fully connected layers or forward propagation in convolutional layers. The *source* folder holds source files, while the *include* folder contains header files.  

#### **Test_Operators**  
Includes source code and header files for unit testing and model validation.  

#### **configs**  
Stores JSON configuration files defining the model's layer details.  

#### **data**  
Holds input, output, weights, and reference files for each layer. Additionally, it includes layer outputs from both C++ and Python for unit testing.  

#### **report**  
Contains log files generated from unit and model testing.  

#### **src**  
Includes the main source file along with a Python script for testing purposes.  

#### **.gitignore**  
Excludes unnecessary files (e.g., *.exe*, *.lib*, *.vscode*) from being tracked in the Git repository.  

#### **CMakeLists.txt**  
Defines the project's build process using CMake, specifying source files, dependencies, compiler options, and build targets for cross-platform compatibility and scalability.  
