# Image Processor Assignment

This project is a C++ implementation of an Image Processor application. It includes basic image augmentation features such as increasing brightness, flipping images, adjusting contrast, converting to grayscale, and rotating images. The project uses OpenCV for image processing.

---

## Folder Structure
```plaintext
.
├── build                # Directory for compiled binaries and build files
├── cat.jpg              # Sample image for testing
├── CMakeLists.txt       # CMake configuration file for building the project
├── include
│   └── image_processor.h # Header file for the ImageProcessor class
├── second.cpp           # Additional code file (optional)
└── src
    └── image_processor.cpp # Implementation of the ImageProcessor class
```

---

## Features
1. **Increase Brightness**: Adjust the brightness of an image by a fixed value.
2. **Horizontal Flip**: Flip the image along the horizontal axis.
3. **Vertical Flip**: Flip the image along the vertical axis.
4. **Adjust Contrast**: Modify the contrast of an image using alpha and beta values.
5. **Convert to Grayscale**: Convert the image to grayscale using standard channel weights.
6. **Rotate 90 Degrees**: Rotate the image 90 degrees clockwise or counterclockwise.

---

## How to Build and Run

### Prerequisites
- A C++ compiler (e.g., `g++` or `clang`)
- CMake (version 3.10 or higher)
- OpenCV library installed on your system

### Build Steps
1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd <repository-folder>
   ```
2. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```
3. Run CMake to configure the project:
   ```bash
   cmake ..
   ```
4. Build the project:
   ```bash
   make
   ```

### Run the Application
1. After a successful build, an executable file will be generated in the `build` directory.
2. Run the application:
   ```bash
   ./ImageProcessorApplication
   ```
3. Provide the input image path and choose the augmentation operation from the available options.

---

## Code Overview

### `image_processor.h`
Declares the `ImageProcessor` class and its member functions:
- `void increaseBrightness(Mat image);`
- `void horizontalFlipImage(Mat image);`
- `void verticalFlipImage(Mat image);`
- `void contrastHandler(Mat image);`
- `void toGrayscale(Mat image);`
- `void rotateImage90(Mat image);`
- `bool saveImageToDisk(const Mat &image, const std::string &filename);`

### `image_processor.cpp`
Implements the functionalities defined in `image_processor.h` using OpenCV methods and manual pixel manipulations.

### `main.cpp`
Handles user interaction and integrates the `ImageProcessor` class to:
- Read the input image
- Apply the selected image augmentation method
- Save the processed image to disk

