#include <opencv2/opencv.hpp>
#include <iostream>
#include "image_operations.h"

// Custom function to convert BGR to HSV
void convertBGRtoHSV(const cv::Mat& inputImage, cv::Mat& outputImage) {
    // Create an output image of the same size but with 3 channels (HSV)
    outputImage = cv::Mat(inputImage.size(), CV_8UC3);

    for (int row = 0; row < inputImage.rows; ++row) {
        for (int col = 0; col < inputImage.cols; ++col) {
            // Get BGR pixel values
            int B = inputImage.at<cv::Vec3b>(row, col)[0];
            int G = inputImage.at<cv::Vec3b>(row, col)[1];
            int R = inputImage.at<cv::Vec3b>(row, col)[2];

            // Normalize RGB values to the range [0, 1]
            float r = R / 255.0f;
            float g = G / 255.0f;
            float b = B / 255.0f;

            // Find the maximum, minimum, and delta between RGB values
            float maxVal = std::max({r, g, b});
            float minVal = std::min({r, g, b});
            float delta = maxVal - minVal;

            // Hue calculation
            float hue = 0.0f;
            if (delta != 0.0f) {
                if (maxVal == r) {
                    hue = (g - b) / delta;
                } else if (maxVal == g) {
                    hue = 2.0f + (b - r) / delta;
                } else {
                    hue = 4.0f + (r - g) / delta;
                }

                hue *= 60.0f;  // Convert to degrees
                if (hue < 0.0f) {
                    hue += 360.0f; // Ensure hue is in the range [0, 360]
                }
            }

            // Saturation calculation
            float saturation = (maxVal == 0.0f) ? 0.0f : (delta / maxVal);

            // Value calculation
            float value = maxVal;

            // Convert HSV values to the range [0, 255]
            int h = static_cast<int>(hue / 2); // Hue [0, 360] -> [0, 180]
            int s = static_cast<int>(saturation * 255);
            int v = static_cast<int>(value * 255);

            // Store the HSV values in the output image
            outputImage.at<cv::Vec3b>(row, col)[0] = h; // Hue
            outputImage.at<cv::Vec3b>(row, col)[1] = s; // Saturation
            outputImage.at<cv::Vec3b>(row, col)[2] = v; // Value
        }
    }
}
