#include "file_io.h"
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>

bool read_image_file(const std::string& imagePath, std::vector<float>& outputVector) {
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image at " << imagePath << std::endl;
        return false;
    }

    cv::Mat resizedImage;
    cv::resize(image, resizedImage, cv::Size(32, 32));

    outputVector.clear();
    for (int row = 0; row < resizedImage.rows; ++row) {
        for (int col = 0; col < resizedImage.cols; ++col) {
            cv::Vec3b pixel = resizedImage.at<cv::Vec3b>(row, col);
            outputVector.push_back(static_cast<float>(pixel[0]) / 255.0f); 
            outputVector.push_back(static_cast<float>(pixel[1]) / 255.0f); 
            outputVector.push_back(static_cast<float>(pixel[2]) / 255.0f); 
        }
    }
    return true;
}

// void write_output_to_file(const std::vector<float>& outputVector, const std::string& layer_name) {
//     std::ofstream outFile("../Report/" + layer_name + ".txt");
//     if (!outFile) {
//         std::cerr << "Error: Unable to open file for writing: " << layer_name + ".txt" << std::endl;
//         return;
//     }

//     for (const float& value : outputVector) {
//         outFile << value << "\n";
//     }
//     outFile.close();
// }

void write_output_to_file(const std::vector<float>& output, const std::string& layer_name) {
    std::string filename = "../Report/output/" + layer_name + "_output.bin";
    
    std::ofstream outfile(filename, std::ios::out | std::ios::binary);
    if (outfile.is_open()) {
        outfile.write(reinterpret_cast<const char*>(output.data()), output.size() * sizeof(float));
        outfile.close();
        std::cout << "Layer output saved to " << filename << std::endl;
    } else {
        std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
    }
}


std::vector<float> read_binary_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return {};
    }
    
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<float> data(size / sizeof(float));
    file.read(reinterpret_cast<char*>(data.data()), size);

    if (!file) {
        std::cerr << "Error: Could not read the file " << filename << std::endl;
        return {};
    }

    return data;
}