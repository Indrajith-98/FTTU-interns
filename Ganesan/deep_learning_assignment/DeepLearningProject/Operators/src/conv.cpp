#include <iostream>
#include <fstream>
#include "conv.h"

void conv(const std::vector<float>& input, const std::vector<float>& weights,
          std::vector<float>& output, int input_size, int stride, int padding, int kernel_size) {

    std::cout << "✅ Running Convolution Operation..." << std::endl;

    int output_size = (input_size - kernel_size + 2 * padding) / stride + 1;
    output.resize(output_size * output_size);

    std::cout << "🔍 Expected output size: " << output_size * output_size << " elements" << std::endl;

    for (int i = 0; i < output_size; ++i) {
        for (int j = 0; j < output_size; ++j) {
            float sum = 0;
            for (int ki = 0; ki < kernel_size; ++ki) {
                for (int kj = 0; kj < kernel_size; ++kj) {
                    int row = i * stride + ki - padding;
                    int col = j * stride + kj - padding;
                    if (row >= 0 && row < input_size && col >= 0 && col < input_size) {
                        sum += input[row * input_size + col] * weights[ki * kernel_size + kj];
                    }
                }
            }
            output[i * output_size + j] = sum;
        }
    }

    // ✅ Debug: Print output size in bytes
    std::cout << "📏 Convolution Output Size (bytes): " << output.size() * sizeof(float) << std::endl;

    // ✅ Debug: Print first 10 output values
    std::cout << "🔢 Conv Output Sample: ";
    for (int i = 0; i < std::min(10, (int)output.size()); i++) {
        std::cout << output[i] << " ";
    }
    std::cout << std::endl;
}
