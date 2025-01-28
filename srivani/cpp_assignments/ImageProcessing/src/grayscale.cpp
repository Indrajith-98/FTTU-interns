#include "GrayscaleConversion.h"
#include <opencv2/opencv.hpp>

void convertToGrayscale(const std::string& imagePath, const std::string& outputPath) {
    cv::Mat image = cv::imread(imagePath);
    if (image.empty()) {
        throw std::runtime_error("Failed to load image from path: " + imagePath);
    }
    
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    
    // Save the grayscale image
    cv::imwrite(outputPath, grayImage);
}
