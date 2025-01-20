#include "ImageProcessing.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

int main() {
    // Input image path
    std::string inputPath = "F:/MCW/Assignment 2/test images/cat.jpeg";

    // Output directory
    std::string outputDir = "F:/MCW/CPP_assignments/Image_Preprocessing/output_images";

    // Create the output directory if it doesn't exist
    if (!std::filesystem::exists(outputDir)) {
        std::filesystem::create_directories(outputDir);
    }

    // Read the image
    auto image = ImageProcessor::readImage(inputPath);

    // Apply grayscale and save
    auto grayImage = ImageProcessor::grayscale(image);
    ImageProcessor::writeImage(outputDir + "/gray_image.jpg", grayImage);

    // Apply inversion and save
    auto invertedImage = ImageProcessor::invert(image);
    ImageProcessor::writeImage(outputDir + "/inverted_image.jpg", invertedImage);

    // Adjust brightness and save
    auto brightImage = ImageProcessor::adjustBrightness(image, 50);
    ImageProcessor::writeImage(outputDir + "/bright_image.jpg", brightImage);

    // Apply normalization and save
    auto normalizedImage = ImageProcessor::normalize(image);
    ImageProcessor::writeImage(outputDir + "/normalized_image.jpg", normalizedImage);

    // Apply Gaussian blur and save
    auto blurredImage = ImageProcessor::gaussianBlur(image);
    ImageProcessor::writeImage(outputDir + "/blurred_image.jpg", blurredImage);

    std::cout << "Processing complete. Check the output images in: " << outputDir << "\n";
    return 0;
}
