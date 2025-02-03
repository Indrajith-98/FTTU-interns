#include "convolution.h"
#include "utils.h"
#include <iostream>
#include <cmath>

Convolution::Convolution(const nlohmann::json& layerConfig) {
    kernel_size = layerConfig["attributes"]["kernel_size"][0];
    stride = layerConfig["attributes"]["strides"][0];
    padding = layerConfig["attributes"]["padding"];
}

void Convolution::forward(const std::string& inputPath, const std::vector<std::string>& weightPaths, const std::string& outputPath) {
    std::vector<float> input = readBinaryFile(inputPath);
    std::vector<float> weights = readBinaryFile(weightPaths[0]); // Assuming single weight file

    int outputSize = (32 - kernel_size) / stride + 1; // Example calculation
    std::vector<float> output(outputSize * outputSize, 0.0f);

    for (int i = 0; i < outputSize; ++i) {
        for (int j = 0; j < outputSize; ++j) {
            float sum = 0.0f;
            for (int k = 0; k < kernel_size; ++k) {
                for (int l = 0; l < kernel_size; ++l) {
                    sum += input[(i + k) * 32 + (j + l)] * weights[k * kernel_size + l];
                }
            }
            output[i * outputSize + j] = sum;
        }
    }

    writeBinaryFile(outputPath, output);
    std::cout << "Conv2D layer processed: " << outputPath << std::endl;
}
