#include "batch_norm.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <string>

void batch_normalization(const std::vector<float>& input, std::vector<float>& output,
                         const std::vector<float>& gamma, const std::vector<float>& beta,
                         const std::vector<float>& moving_mean, const std::vector<float>& moving_variance,
                         float epsilon, size_t channels, size_t height, size_t width, const std::string layer_name) {
    size_t spatial_size = height * width;
    output.resize(input.size());

    for (int c = 0; c < channels; ++c) {
        for (int h = 0; h < height; ++h) {
            for (int w = 0; w < width; ++w) {
                int idx = (h * width + w) * channels + c;
                output[idx] = gamma[c] * (input[idx] - moving_mean[c]) / std::sqrt(moving_variance[c] + epsilon) + beta[c];
            }
        }
    }

    std::cout << "BatchNorm Output Size = " << output.size() << std::endl;

    std::string output_file = "F:/MultiCoreWare/C++ Application/Project_Root/data/cpp_layer_outputs/" + layer_name + ".txt";
    std::ofstream file(output_file);

    if (file.is_open()) {

        for (size_t i = 0; i < output.size(); ++i) {
            file << std::fixed << std::setprecision(6) << output[i] << "\n";
        }

        file.close();
        std::cout << "Saved BatchNorm output to " << output_file << std::endl;
    } else {
        std::cerr << "Failed to open file for writing: " << output_file << std::endl;
    }
}