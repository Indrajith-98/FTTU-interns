



#include "DenseLayer.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <chrono>  
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
    auto start_time = std::chrono::high_resolution_clock::now();

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
    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> execution_time = end_time - start_time;

    std::cout << "Dense Layer Execution Time: " << execution_time.count() << " seconds" << std::endl;

    // Write the output to a text file
    std::ofstream outfile("O:/C++ Operators and Layers - M/LayerWiseOutput/CppLayerWiseOutput/"+layer_name+".txt");
    if (outfile.is_open()) {
        for (int i = 0; i < output_size; i++) {
            outfile << output[i] << " ";
        }
        outfile << "\n";
        outfile.close();
    std::cout << "Output of First channel saved to LayerWiseOutput/CppLayerWiseOutput"+layer_name+".txt" << std::endl;
    } else {
        std::cerr << "Error opening file for writing!" << std::endl;
    }

    std::cout << "\n\n";

    std::cout << "Dense Output Size = " << output.size() << std::endl;
}