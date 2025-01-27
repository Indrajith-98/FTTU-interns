#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include <vector>

// Function to add padding to the input matrix
void add_padding(std::vector<std::vector<float>>& input, int padding);

// Function to perform 2D convolution with stride and padding
void convolve2d(const std::vector<std::vector<float>>& input, 
                const std::vector<std::vector<float>>& kernel,
                std::vector<std::vector<float>>& output,
                int stride, int padding);

// Function to apply ReLU activation
void relu(std::vector<std::vector<float>>& input);

// Function to print a matrix
void print_matrix(const std::vector<std::vector<float>>& matrix);

#endif // CONVOLUTION_H
