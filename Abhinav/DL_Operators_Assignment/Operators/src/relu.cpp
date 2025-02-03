#include "relu.h"
#include "utils.h"
#include <iostream>
#include <vector>

void ReLU::forward(const std::string& inputPath, const std::string& outputPath) {
    std::vector<float> input = readBinaryFile(inputPath);
    std::vector<float> output(input.size());

    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = std::max(0.0f, input[i]);
    }

    writeBinaryFile(outputPath, output);
    std::cout << "ReLU layer processed: " << outputPath << std::endl;
}
