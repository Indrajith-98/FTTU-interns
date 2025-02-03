#include <stdexcept>
#include <iostream>
#include <vector>
#include "max_pool.h"

// Constructor for MaxPooling class
MaxPooling::MaxPooling(int pool_height, int pool_width)
    : pool_height(pool_height), pool_width(pool_width) {
    // Pooling dimensions can be initialized or checked for validity here if needed
}

// Function to perform 2D max pooling
std::vector<std::vector<std::vector<double>>> MaxPooling::performMaxPooling(
    const std::vector<std::vector<std::vector<double>>>& input_image,  // 3D input image
    int image_depth, int image_height, int image_width,
    int stride, int padding
) {
    int output_height = (image_height - pool_height + 2 * padding) / stride + 1;
    int output_width = (image_width - pool_width + 2 * padding) / stride + 1;

    // Initialize the output as a 3D vector
    std::vector<std::vector<std::vector<double>>> output(
        image_depth, std::vector<std::vector<double>>(
            output_height, std::vector<double>(output_width, 0)));

    // Perform max pooling for each depth slice
    for (int d = 0; d < image_depth; ++d) {
        for (int i = 0; i < output_height; ++i) {
            for (int j = 0; j < output_width; ++j) {
                double max_value = -std::numeric_limits<double>::infinity();
                // Iterate through the pooling window
                for (int m = 0; m < pool_height; ++m) {
                    for (int n = 0; n < pool_width; ++n) {
                        int x = i * stride + m - padding;
                        int y = j * stride + n - padding;
                        if (x >= 0 && x < image_height && y >= 0 && y < image_width) {
                            max_value = std::max(max_value, input_image[d][x][y]);
                        }
                    }
                }
                // Store the max value in the output
                output[d][i][j] = max_value;
            }
        }
    }
    return output;
}

