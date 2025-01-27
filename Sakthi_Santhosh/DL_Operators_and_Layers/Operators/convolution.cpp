#include "convolution.h"
#include <iostream>

// Function to add padding to the input matrix
void add_padding(std::vector<std::vector<float>>& input, int padding) {
    int inputHeight = input.size();
    int inputWidth = input[0].size();

    // Create a new matrix with padding
    std::vector<std::vector<float>> paddedInput(inputHeight + 2 * padding, 
                                                std::vector<float>(inputWidth + 2 * padding, 0));

    // Copy the input into the padded matrix
    for (int i = 0; i < inputHeight; ++i) {
        for (int j = 0; j < inputWidth; ++j) {
            paddedInput[i + padding][j + padding] = input[i][j];
        }
    }

    // Update the input matrix to be the padded matrix
    input = paddedInput;
}

// Function to perform 2D convolution with stride and padding
void convolve2d(const std::vector<std::vector<float>>& input, 
                const std::vector<std::vector<float>>& kernel,
                std::vector<std::vector<float>>& output,
                int stride, int padding) {
    int inputHeight = input.size();
    int inputWidth = input[0].size();
    int kernelHeight = kernel.size();
    int kernelWidth = kernel[0].size();

    // Calculate output dimensions
    int outputHeight = (inputHeight - kernelHeight + 2 * padding) / stride + 1;
    int outputWidth = (inputWidth - kernelWidth + 2 * padding) / stride + 1;

    // Initialize the output matrix
    output.resize(outputHeight, std::vector<float>(outputWidth, 0));

    // Perform convolution
    for (int i = 0; i < outputHeight; ++i) {
        for (int j = 0; j < outputWidth; ++j) {
            float sum = 0.0f;
            for (int ki = 0; ki < kernelHeight; ++ki) {
                for (int kj = 0; kj < kernelWidth; ++kj) {
                    int inputRow = i * stride + ki;
                    int inputCol = j * stride + kj;
                    sum += input[inputRow][inputCol] * kernel[ki][kj];
                }
            }
            output[i][j] = sum;
        }
    }
}

// Function to apply ReLU activation
void relu(std::vector<std::vector<float>>& input) {
    int height = input.size();
    int width = input[0].size();

    // Apply ReLU (set negative values to 0)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (input[i][j] < 0) {
                input[i][j] = 0;
            }
        }
    }
}

// Function to print a matrix
void print_matrix(const std::vector<std::vector<float>>& matrix) {
    for (const auto& row : matrix) {
        for (float val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}
