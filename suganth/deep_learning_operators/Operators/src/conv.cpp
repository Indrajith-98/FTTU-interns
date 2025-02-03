#include "conv.h"
#include <stdexcept>
#include <iostream>
// Constructor for Convolution class
Convolution::Convolution(int kernel_height, int kernel_width, int kernel_depth )
    : kernel_height(kernel_height), kernel_width(kernel_width), kernel_depth(kernel_depth) {
    // Kernel dimensions can be initialized or checked for validity here if needed
}


// Function to perform 2D convolution with a 3D kernel (multiple filters)
std::vector<std::vector<double>> Convolution::performConvolution(
    const std::vector<std::vector<std::vector<double>>>& input_image,  // 3D input image
    int image_depth, int image_height, int image_width,
    const std::vector<std::vector<std::vector<double>>>& kernels,  // 3D kernel (multiple filters)
    const double bias,
    int stride , int padding
) {

    int num_filters = static_cast<int>(kernels.size()); // Number of filters

    int output_height = (image_height - kernel_height + 2 * padding) / stride + 1;
    int output_width = (image_width - kernel_width + 2 * padding) / stride + 1;

    // Initialize the output as a 2D vector (for a single filter's convoluted output)
    std::vector<std::vector<double>> output(output_height, std::vector<double>(output_width, 0));

    // Perform convolution for each filter
    for (int f = 0; f < image_depth; ++f) {
        for (int i = 0; i < output_height; ++i) {
            for (int j = 0; j < output_width; ++j) {
                double value = 0.0;
                // Iterate through the kernel dimensions
                for (int d = 0; d < kernel_depth; ++d) { // Loop over depth
                    for (int m = 0; m < kernel_height; ++m) { // Loop over filter height
                        for (int n = 0; n < kernel_width; ++n) { // Loop over filter width
                            int x = i * stride + m - padding;
                            int y = j * stride + n - padding;
                            if (x >= 0 && x < image_height && y >= 0 && y < image_width) {
                                value += input_image[d][x][y] * kernels[d][m][n];
                            }
                        }
                    }
                }

                value += bias;

                // Apply ReLU activation (if required)
                value = std::max(0.0, value); // ReLU activation

                // Store in output
                output[i][j] = value;
            }
        }
    }
    return output;
}