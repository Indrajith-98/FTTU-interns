#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include "ImageProcessor.h"

std::vector<std::vector<std::vector<unsigned char>>>  ImageProcessor::readImage(const std::string& imagePath) {
    cv::Mat img = cv::imread(imagePath, cv::IMREAD_COLOR); // Read the image
    if (img.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        exit(1);
    }

    // Convert the cv::Mat to a 3D vector of unsigned char (RGB channels)
    int rows = img.rows;
    int cols = img.cols;
    std::vector<std::vector<std::vector<unsigned char>>> image(rows, std::vector<std::vector<unsigned char>>(cols, std::vector<unsigned char>(3)));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cv::Vec3b color = img.at<cv::Vec3b>(i, j);
            image[i][j][0] = color[0]; // Blue
            image[i][j][1] = color[1]; // Green
            image[i][j][2] = color[2]; // Red
        }
    }

    return image;  // Return the image as a 3D vector
}
