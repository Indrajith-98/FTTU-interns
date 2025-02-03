# ImageProcessor - C++ Project for Image Processing

## Overview
The `ImageProcessor` class provides a set of methods for performing basic image processing operations such as grayscale conversion, resizing, edge detection, histogram equalization, and image sharpening. This project uses OpenCV for reading and writing image files.

## Features
1. **Image Loading and Saving**: The class supports loading and saving images from and to disk using OpenCV.
2. **Grayscale Conversion**: Converts the image to grayscale using a standard formula.
3. **Resize Image**: Resizes an image to a new width and height using nearest-neighbor interpolation.
4. **Edge Detection**: Detects edges in the image using the Sobel operator.
5. **Histogram Equalization**: Enhances the contrast of the image by equalizing its histogram.
6. **Image Sharpening**: Sharpens the image using a simple 3x3 convolution kernel.
7. **Image Display**: Displays the image's pixel values for debugging purposes.

## Dependencies
This project uses OpenCV for image loading, processing, and saving. You will need to install OpenCV to run this code.

To install OpenCV in C++:

1. Download OpenCV from [here](https://opencv.org/releases/).
2. Follow the installation instructions specific to your operating system.

## Usage

1. **Clone or Download** the project files.
2. **Configure OpenCV** in your C++ development environment (e.g., Visual Studio, Code::Blocks).
3. **Build and Run** the project.

## Example Workflow

1. **Loading an image**:
   - The image is loaded from a specified file path using `loadImage`.
   - Ensure the image path is correct.

2. **Operations**:
   - `toGrayscale()` - Converts the image to grayscale.
   - `resizeImage(newWidth, newHeight)` - Resizes the image to the specified dimensions.
   - `detectEdges()` - Applies Sobel edge detection.
   - `histogramEqualization()` - Equalizes the image histogram.
   - `sharpenImage()` - Sharpens the image using a 3x3 convolution kernel.

3. **Saving**:
   - The processed images are saved to the disk using `saveImage` with different filenames (e.g., "grayscale_image.jpg").

4. **Display**:
   - The `displayImage()` method will print out the RGB values of each pixel for debugging (optional).

## Example Code:

```cpp
ImageProcessor processor(0, 0);

// Load an image
processor.loadImage("/home/ganesan/python/FTTU-interns/Ganesan/cpp_assignments/image_processing/img/cards.jpg");

// Perform operations
processor.toGrayscale();
processor.saveImage("grayscale_image.jpg");

processor.resizeImage(3840, 2160);
processor.saveImage("resized_image.jpg");

processor.detectEdges();
processor.saveImage("edge_detected_image.jpg");

processor.histogramEqualization();
processor.saveImage("histogram_equalized_image.jpg");

processor.sharpenImage();
processor.saveImage("sharpened_image.jpg");
