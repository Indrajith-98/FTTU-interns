#include "utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>

std::vector<float> read_weights_from_file(const std::string& file_path) {
    std::vector<float> weights;
    std::ifstream file(file_path);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + file_path);
    }

    float value;
    while (file >> value) {
        weights.push_back(value);
    }

    file.close();
    return weights;
}


// Utility function to print a 3D vector
void print_3d_vector(const std::vector<std::vector<std::vector<float>>> &vec, const std::string &file_path) {
    std::ofstream result_file(file_path);
    for (const auto &matrix : vec) {
        for (const auto &row : matrix) {
            for (float val : row) {
                result_file << val << " ";
            }
            // result_file << "\n";
        }
        result_file << "\n";
    }
}

// Utility function to print a 1D vector
void print_1d_vector(const std::vector<float> &vec, const std::string &file_path) {
    std::ofstream result_file(file_path);
    for (float val : vec) {
        result_file << val << " ";
    }
    result_file << "\n";
}

// Function to read the image data from the file and return as a 3D tensor
std::vector<std::vector<std::vector<float>>> read_image_from_file(const std::string& filename, int width, int height) {
    std::ifstream file(filename);
    std::vector<std::vector<std::vector<float>>> image_data(3, std::vector<std::vector<float>>(height, std::vector<float>(width)));

    if (file.is_open()) {
        std::string line;
        int row = 0;
        while (std::getline(file, line) && row < height) {
            std::istringstream iss(line);
            float r, g, b;
            int col = 0;
            while (iss >> r >> g >> b && col < width) {
                image_data[0][row][col] = r;  // Red channel
                image_data[1][row][col] = g;  // Green channel
                image_data[2][row][col] = b;  // Blue channel
                col++;
            }
            row++;
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open the file!" << std::endl;
    }

    return image_data;
}


template <typename T>
void print_dimensions(const std::string& layer_name, const T& tensor) {
    if constexpr (std::is_same_v<T, std::vector<std::vector<std::vector<float>>>>) {
        // For 3D tensors
        std::cout << layer_name << " Output Dimensions: "
                  << tensor.size() << "x" << tensor[0].size() << "x" << tensor[0][0].size()
                  << std::endl;
    } else if constexpr (std::is_same_v<T, std::vector<float>>) {
        // For 1D tensors
        std::cout << layer_name << " Output Dimensions: " << tensor.size() << std::endl;
    }
}


