#include "softmax.h"
#include "utils.h"
#include <iostream>
#include <cmath>
#include <vector>

void Softmax::forward(const std::string& inputPath, const std::string& outputPath) {
    std::vector<float> input = readBinaryFile(inputPath);
    std::vector<float> output(input.size());

    float maxVal = *std::max_element(input.begin(), input.end());
    float sumExp = 0.0f;

    for (float val : input) {
        sumExp += std::exp(val - maxVal);
    }

    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = std::exp(input[i] - maxVal) / sumExp;
    }

    writeBinaryFile(outputPath, output);
    std::cout << "Softmax layer processed: " << outputPath << std::endl;
}
