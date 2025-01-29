# **Image Processing**

## **Task Overview**
This assignment involves implementing five image preprocessing techniques—Resize, Normalize, RGB to Grayscale, Random Crop, and Random Rotation—using direct pixel manipulation in C++. OpenCV is used for loading and saving images.

**Resize**: Adjusts the image dimensions using interpolation.
**Normalize**: Scales pixel values to a specified range for consistency.
**RGB to Grayscale**: Converts a color image to grayscale by computing luminance.
**Random Crop**: Extracts a randomly selected region from the image.
**Random Rotation**: Rotates the image by a random angle while handling pixel mapping.

## **Project Folder Contents**

### **build**
Contains compiled binaries, object files, Makefiles, and CMake-generated configuration files.

### **include**
Contains the header files of the each image processing technique, which contains the function definitions of every technique.

### **src**
Cotnains the source files, which contains the implementation of the image processing techniques.

### **CMakeLists.txt**
A configuration file used by CMake to define how the project should be built, including source files, dependencies, compiler options, and build targets, ensuring platform-independent and scalable builds.