#include <iostream>
#include "GrayscaleConversion.h"
#include "RandomCrop.h"
#include "RandomHorizontalShift.h"
#include "ImageBlur.h"  // Include the blur header file
#include "EdgeDetection.h"
#include <opencv2/opencv.hpp>

int main() {
    try {
        // Define input and output image paths
        std::string inputImagePath = "C:/Users/7501/Desktop/ImageProcessing/Leaf.jpg";  // Replace with your input image path
        std::string outputImagePath = "output_gray.jpg";  // Replace with your desired output path

        // Call the grayscale conversion function
        convertToGrayscale(inputImagePath, outputImagePath);
        
        std::cout << "Grayscale conversion successful! Output saved to " << outputImagePath << std::endl;

        // Load the image for random crop and horizontal shift
        cv::Mat image = cv::imread(inputImagePath);
        if (image.empty()) {
            throw std::runtime_error("Failed to load image from path: " + inputImagePath);
        }

        // Apply grayscale conversion
        cv::Mat grayImage;
        cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

        // Show the grayscale image
        cv::imshow("Grayscale Image", grayImage);
        cv::waitKey(0);

        // Apply random crop (e.g., 100x100)
        cv::Mat croppedImage = randomCrop(image, 350, 150);
        cv::imshow("Random Crop", croppedImage);
        cv::waitKey(0);

        // Apply random horizontal shift (e.g., maximum shift of 50 pixels)
        cv::Mat shiftedImage = randomHorizontalShift(image, 50);
        cv::imshow("Random Horizontal Shift", shiftedImage);
        cv::waitKey(0);

        // Apply Gaussian blur (e.g., kernel size of 5)
        cv::Mat blurredImage = applyGaussianBlur(image, 35);
        cv::imshow("Blurred Image", blurredImage);
        cv::waitKey(0);

         // Apply edge detection with custom thresholds (e.g., 50 and 150)
        cv::Mat edgeImage = applyEdgeDetection(image, 50, 150);
        cv::imshow("Edge Detection", edgeImage);
        cv::waitKey(0);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}
