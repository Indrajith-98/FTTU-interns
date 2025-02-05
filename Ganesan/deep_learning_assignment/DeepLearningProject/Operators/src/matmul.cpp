#include "matmul.h"
#include <iostream>

std::vector<float> MatMul::forward(const std::vector<float>& input, 
                                   const std::vector<float>& weights, 
                                   const std::vector<float>& bias, 
                                   int input_size, int output_size) {

    std::vector<float> output(output_size, 0.0f);

    for (int i = 0; i < output_size; ++i) {
        for (int j = 0; j < input_size; ++j) {
            output[i] += input[j] * weights[i * input_size + j];
        }
        output[i] += bias[i];  // Add bias term
    }

    return output;
}
