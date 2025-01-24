#include "ImageProcessor.h"
#include <iostream>

ImageProcessor::ImageProcessor(const std::string& imagePath) {
    loadImage(imagePath);
}

void ImageProcessor::loadImage(const std::string& imagePath) {
    cv::Mat img = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Error: Failed to open file " << imagePath << std::endl;
        exit(1);
    }
    width = img.cols;
    height = img.rows;
    channels = img.channels();
    image.assign(img.data, img.data + img.total() * img.channels());
}

void ImageProcessor::save(const std::string& outputPath) {
    cv::Mat output(height, width, CV_8UC3, image.data());
    cv::imwrite(outputPath, output);
}
