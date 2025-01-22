#include "image_operations.h"

void adjustSaturation(const cv::Mat& inputImage, cv::Mat& outputImage, float saturationFactor) {
    // Convert BGR to HSV
    cv::Mat hsvImage;
    convertBGRtoHSV(inputImage, hsvImage);

    for (int row = 0; row < hsvImage.rows; ++row) {
        for (int col = 0; col < hsvImage.cols; ++col) {
            // Get HSV pixel values
            int h = hsvImage.at<cv::Vec3b>(row, col)[0];
            int s = hsvImage.at<cv::Vec3b>(row, col)[1];
            int v = hsvImage.at<cv::Vec3b>(row, col)[2];

            // Adjust saturation
            float newS = static_cast<float>(s) * saturationFactor;

            // Clamp saturation to the range [0, 255]
            newS = std::min(std::max(newS, 0.0f), 255.0f);

            // Update the HSV image
            hsvImage.at<cv::Vec3b>(row, col)[1] = static_cast<uchar>(newS);
        }
    }

    // Convert HSV back to BGR
    cv::cvtColor(hsvImage, outputImage, cv::COLOR_HSV2BGR);
}
