# **Deep Learning Operators and Layers in C++**

## **Project Overview**

This project implements the core functionality of deep-learning layers using C++. It simulates a deep-learning model by executing each layer sequentially, based on a configuration file. Each layer is implemented with its respective floating-point operations and tested against pre-defined inputs. The application generates log files with execution details and validates the outputs against reference results.

## **Project Folder Contents**

### **Operators**

Contains the source code and headers for implementing deep learning operators like convolution, batch normalization, max pooling and dense. The **src** folder contains the source files and the **include** folder contains the header files.

### **Test_Operators**

Contains the source code and headers for unit and model testing. The **src** folder contains the source files and the **include** folder contains the header files.

### **build**

Contains compiled binaries, object files, Makefiles, and CMake-generated configuration files.

### **configs**

Contains the json configuration file containing the details of each of the layers of the CNN model.

### **data**

Contains the **input**, **output**, **weights** and **reference** files for each of the layers. Also contains the **layer outputs** of C++ and python for validation.

### **report**

Contains the log files for **inferencing**, **unit testing** and **model testing**.

### **src**

Contains the **main** source file and a **.py file** for testing purposes.

### **utilities**

Contains the source code and headers for the utils file which facilitates **file handling** and **image preprocessing**. The **src** folder contains the source files and the **include** folder contains the header files.

### **.gitignore**

Ensures unnecessary files (e.g., .exe, .lib, .vscode) are not tracked in the Git repository.

### **CMakeLists.txt**

A configuration file used by CMake to define how the project should be built, including source files, dependencies, compiler options, and build targets, ensuring platform-independent and scalable builds.

## **Environment**

**Operating System**: Windows 11

**Compiler**: MSVC Compiler v.19.42.34435

**Cmake**: v.3.31.3

**C++**: C++14

**Git**: v.2.41.0.windows.3