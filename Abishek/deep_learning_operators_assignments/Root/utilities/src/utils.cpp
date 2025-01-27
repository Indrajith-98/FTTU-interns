#include "utils.h"
#include <fstream>
#include <cassert>
#include <iostream>
#include <vector>
#include <opencv4/opencv2/opencv.hpp>
#include <nlohmann/json.hpp>

// Function to load a binary file and return its contents as a vector
std::vector<float> load_binary_file(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        exit(1);
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<float> data(size / sizeof(float));
    file.read(reinterpret_cast<char*>(data.data()), size);
    file.close();

    return data;
}


std::vector<float> loadImage(const std::string& filepath) {

    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

    cv::Mat image = cv::imread(filepath, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Error: Could not load the image at " << filepath << std::endl;
    }

    // BGR to RGB
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);

    // Resize the image to 32x32
    cv::Mat resizedImage;
    cv::resize(image, resizedImage, cv::Size(32, 32));

    // Flatten the image (H x W x C into 1D vector)
    std::vector<float> flattenedImage;
    for (int row = 0; row < resizedImage.rows; ++row) {
        for (int col = 0; col < resizedImage.cols; ++col) {
            cv::Vec3b pixel = resizedImage.at<cv::Vec3b>(row, col);
            for (int channel = 0; channel < resizedImage.channels(); ++channel) {
                flattenedImage.push_back(pixel[channel] / 255.0f); // Normalize (0-255 to 0.0-1.0)
            }
        }
    }

    // Print the normalized and flattened vector size
    std::cout << "Input Image size: " << flattenedImage.size() << std::endl;
    std::cout << "=======================================================================" << std::endl;
    // Optionally, print the first few values for verification
    // for (size_t i = 0; i < std::min(flattenedImage.size(), size_t(10)); ++i) {
    //     std::cout << flattenedImage[i] << " ";
    // }
    // std::cout << std::endl;

    return flattenedImage;
}

nlohmann::json load_json_config(const std::string& file_path) {
    std::ifstream config_file(file_path);
    if (!config_file) {
        std::cerr << "Error opening config file." << std::endl;
    }

    nlohmann::json config;
    config_file >> config;
    return config;
}