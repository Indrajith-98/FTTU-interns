#include "ImageProcessing.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

int main() {
    // Input image path
    std::string inputPath = "F:/MCW/Assignment 2/test images/cat.jpeg";

    // Output directory
    std::string outputDir = "F:/MCW/training assignments/CPP_assignments/Image_Preprocessing/output_images";

    // Create the output directory if it doesn't exist
    if (!std::filesystem::exists(outputDir)) {
        std::filesystem::create_directories(outputDir);
    }

    // Read the image using OpenCV
    cv::Mat image = cv::imread(inputPath);

    // Check if the image is loaded successfully
    if (image.empty()) {
        std::cerr << "Error: Could not load the image at " << inputPath << "\n";
        return -1;
    }

    // Apply grayscale and save
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    cv::imwrite(outputDir + "/gray_image.jpg", grayImage);

    // Apply inversion and save
    cv::Mat invertedImage = 255 - image; // Invert the image
    cv::imwrite(outputDir + "/inverted_image.jpg", invertedImage);

    // Adjust brightness and save
    cv::Mat brightImage;
    int brightnessOffset = 50; // Brightness adjustment value
    image.convertTo(brightImage, -1, 1, brightnessOffset); // Adjust brightness
    cv::imwrite(outputDir + "/bright_image.jpg", brightImage);

    // Apply normalization and save
    cv::Mat normalizedImage;
    cv::normalize(image, normalizedImage, 0, 255, cv::NORM_MINMAX);
    cv::imwrite(outputDir + "/normalized_image.jpg", normalizedImage);

    // Apply Gaussian blur and save
    cv::Mat blurredImage;
    cv::GaussianBlur(image, blurredImage, cv::Size(7, 7), 1.5);
    cv::imwrite(outputDir + "/blurred_image.jpg", blurredImage);

    std::cout << "Processing complete. Check the output images in: " << outputDir << "\n";
    return 0;
}
