#include <opencv2/opencv.hpp>
#include "image_operations.h"

// Function to adjust contrast
void adjustContrast(const cv::Mat& inputImage, cv::Mat& outputImage, float factor) {
    outputImage = inputImage.clone();

    for (int row = 0; row < inputImage.rows; ++row) {
        for (int col = 0; col < inputImage.cols; ++col) {
            for (int c = 0; c < inputImage.channels(); ++c) {
                int pixel = inputImage.at<cv::Vec3b>(row, col)[c];
                int newValue = static_cast<int>(factor * (pixel - 128) + 128);
                outputImage.at<cv::Vec3b>(row, col)[c] = std::min(std::max(newValue, 0), 255);
            }
        }
    }
}
