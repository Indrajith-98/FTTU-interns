# Image Processing Project
This project demonstrates various image processing techniques, including grayscale conversion, random crop, random horizontal shift,
Gaussian blur, and edge detection using OpenCV. The application takes an image as input and applies the respective transformations, 
displaying the results in separate windows.

## Features

- **Grayscale Conversion**: Convert an image to grayscale.
- **Random Crop**: Apply a random crop to an image.
- **Random Horizontal Shift**: Apply a random horizontal shift to an image.
- **Gaussian Blur**: Apply a Gaussian blur with customizable kernel size.
- **Edge Detection**: Apply edge detection to an image using custom threshold values.

## Project Structure

### `src/`
Contains the implementation of all the functions used in this project.

### `include/`
Contains header files that declare the functions and classes used in `src/`.

### `CMakeLists.txt`
CMake build configuration file for compiling the project.

### `ImageProcessing.cpp`
An example code to test whether opencv is working or not

## Requirements
To run this project, you will need the following:
- **OpenCV**: OpenCV is a library for computer vision and image processing.
- **C++11 or higher**: This project requires C++11 or a newer version.
- **CMake**: Used to manage the build process of the project.

## Setup Instructions
```bash
git clone https://github.com/your-username/image-processing-project.git
cd image-processing-project
mkdir build
cd build
cmake ..
cmake --build .
./image_processing_app
```

## Output images
![Screenshot 2025-01-28 120819](https://github.com/user-attachments/assets/4d040bc4-f3c7-40f7-9344-77ce9ad0c0d3)
![Screenshot 2025-01-28 120742](https://github.com/user-attachments/assets/20233a32-a73b-4188-ba6e-476208b752dd)
![Screenshot 2025-01-28 120754](https://github.com/user-attachments/assets/7609b3c1-37bc-4425-b150-61c49c827da7)
![Screenshot 2025-01-28 120805](https://github.com/user-attachments/assets/df68d8c2-c989-4f75-aff7-eb6cd1daf375)
![Screenshot 2025-01-28 120813](https://github.com/user-attachments/assets/de1c2469-da45-44fe-8f03-ce9fd81f30f4)




