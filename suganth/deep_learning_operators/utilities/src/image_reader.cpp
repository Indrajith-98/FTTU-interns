#include "image_reader.h"

ImageReader::ImageReader(const std::string& filePath) : filePath(filePath) {}

 std::vector<std::vector<std::vector<double>>> ImageReader::readImage() {
    cv::Mat image = cv::imread(filePath, cv::IMREAD_COLOR);
    int channel_size = 1;
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image." << std::endl;
        return {};
    }

    std::vector<std::vector<std::vector<double>>> imageVector(
        channel_size,
        std::vector<std::vector<double>>(image.rows, std::vector<double>(image.cols))
    );

    for (int c = 0; c < channel_size; ++c) {
        for (int i = 0; i < image.rows; ++i) {
            for (int j = 0; j < image.cols; ++j) {
                imageVector[c][i][j] = static_cast<double>(image.at<cv::Vec3b>(i, j)[c]) / 255.0f;
            }
        }
    }
    return imageVector;
}