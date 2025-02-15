#include "dense.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <iomanip>

void relu(std::vector<float>& tensor) {
    for (auto& value : tensor) {
        value = std::max(0.0f, value);
    }
}

void softmax(std::vector<float>& tensor) {
    float max_val = *std::max_element(tensor.begin(), tensor.end());
    float sum = 0.0f;
    for (auto& value : tensor) {
        value = std::exp(value - max_val);
        sum += value;
    }
    for (auto& value : tensor) {
        value /= sum;
    }
}

void dense(const std::vector<float>& input, const std::vector<float>& weights,
           const std::vector<float>& bias, std::vector<float>& output,
           const std::array<int, 2>& input_shape, const std::array<int, 2>& output_shape,
           const std::string& activation, const std::string layer_name) {
    int input_size = input_shape[1];
    int output_size = output_shape[1];

    for (int o = 0; o < output_size; ++o) {
        float sum = 0.0f;
        for (int i = 0; i < input_size; ++i) {
            sum += input[i] * weights[i * output_size + o];
        }
        output[o] = sum + bias[o];
    }

    if (activation == "relu") {
        relu(output);
    } else if (activation == "softmax") {
        softmax(output);
    }

    std::cout << "Dense Output Size = " << output.size() << std::endl;

    std::string output_file = "F:/MultiCoreWare/C++ Application/Project_Root/data/cpp_layer_outputs/" + layer_name + ".txt";
    std::ofstream file(output_file);

    if (file.is_open()) {

        // Write each value on a new line
        for (size_t i = 0; i < output.size(); ++i) {
            file << std::fixed << std::setprecision(6) << output[i] << "\n";
        }

        file.close();
        std::cout << "Saved Dense layer output to " << output_file << std::endl;
    } else {
        std::cerr << "Failed to open file for writing: " << output_file << std::endl;
    }
}