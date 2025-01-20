#include "ImageProcessing.h"
#include <opencv2/opencv.hpp>

std::vector<std::vector<std::vector<unsigned char>>> ImageProcessor::readImage(const std::string& filePath) {
    cv::Mat img = cv::imread(filePath, cv::IMREAD_COLOR);
    if (img.empty()) {
        throw std::runtime_error("Could not open or find the image");
    }

    std::vector<std::vector<std::vector<unsigned char>>> image(
        img.rows, std::vector<std::vector<unsigned char>>(img.cols, std::vector<unsigned char>(3)));

    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            image[i][j][0] = img.at<cv::Vec3b>(i, j)[0]; // Blue
            image[i][j][1] = img.at<cv::Vec3b>(i, j)[1]; // Green
            image[i][j][2] = img.at<cv::Vec3b>(i, j)[2]; // Red
        }
    }

    return image;
}

void ImageProcessor::writeImage(const std::string& filePath, const std::vector<std::vector<std::vector<unsigned char>>>& image) {
    int rows = image.size();
    int cols = image[0].size();
    cv::Mat img(rows, cols, CV_8UC3);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            img.at<cv::Vec3b>(i, j)[0] = image[i][j][0]; // Blue
            img.at<cv::Vec3b>(i, j)[1] = image[i][j][1]; // Green
            img.at<cv::Vec3b>(i, j)[2] = image[i][j][2]; // Red
        }
    }

    if (!cv::imwrite(filePath, img)) {
        throw std::runtime_error("Could not write the image to file");
    }
}
