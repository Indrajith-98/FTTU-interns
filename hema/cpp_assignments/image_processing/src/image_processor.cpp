#include "image_processor.h"
#include <opencv2/opencv.hpp>
#include <iostream>

bool ImageProcessor::loadImage(const std::string &file_path) {
    cv::Mat img = cv::imread(file_path, cv::IMREAD_UNCHANGED);
    if (img.empty()) {
        std::cerr << "Error: Could not load image!" << std::endl;
        return false;
    }

    width = img.cols;
    height = img.rows;
    channels = img.channels();

    image_data.resize(height, std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(channels)));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cv::Vec3b pixel = img.at<cv::Vec3b>(i, j);
            for (int k = 0; k < channels; k++) {
                image_data[i][j][k] = pixel[k];
            }
        }
    }
    return true;
}

void ImageProcessor::saveImage(const std::string &file_path) {
    cv::Mat output_img(height, width, channels == 3 ? CV_8UC3 : CV_8UC1);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (channels == 3) {
                output_img.at<cv::Vec3b>(i, j) = cv::Vec3b(image_data[i][j][0], image_data[i][j][1], image_data[i][j][2]);
            } else {
                output_img.at<unsigned char>(i, j) = image_data[i][j][0];
            }
        }
    }
    cv::imwrite(file_path, output_img);
    std::cout << "Image saved to: " << file_path << std::endl;
}
