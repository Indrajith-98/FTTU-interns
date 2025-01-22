#include "ImageProcessor.h"
#include <opencv2/opencv.hpp>

void ImageProcessor::saveImage(const std::string& outputPath, const std::vector<std::vector<std::vector<unsigned char>>>& img) {
    int rows = img.size();
    int cols = img[0].size();
    cv::Mat mat(rows, cols, CV_8UC3); // Create cv::Mat to save the image

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat.at<cv::Vec3b>(i, j)[0] = img[i][j][0];  // Blue
            mat.at<cv::Vec3b>(i, j)[1] = img[i][j][1];  // Green
            mat.at<cv::Vec3b>(i, j)[2] = img[i][j][2];  // Red
        }
    }

    cv::imwrite(outputPath, mat);  // Save image
}