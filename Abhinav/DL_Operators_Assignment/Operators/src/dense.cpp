#include "dense.h"
#include "utils.h"
#include <iostream>

Dense::Dense(const nlohmann::json& layerConfig) {
    input_size = layerConfig["attributes"]["input_dim"];
    output_size = layerConfig["attributes"]["output_dim"];
}

void Dense::forward(const std::string& inputPath, const std::vector<std::string>& weightPaths, const std::string& outputPath) {
    std::vector<float> input = readBinaryFile(inputPath);
    std::vector<float> weights = readBinaryFile(weightPaths[0]);
    std::vector<float> bias = readBinaryFile(weightPaths[1]);
    
    std::vector<float> output(output_size, 0.0f);

    for (int i = 0; i < output_size; ++i) {
        float sum = bias[i];  // Start with bias
        for (int j = 0; j < input_size; ++j) {
            sum += input[j] * weights[i * input_size + j];
        }
        output[i] = sum;
    }

    writeBinaryFile(outputPath, output);
    std::cout << "Dense layer processed: " << outputPath << std::endl;
}
