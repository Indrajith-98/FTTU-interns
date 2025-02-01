#include "../include/maxpooling.h"
#include <limits>
#include <algorithm>
#include <iostream>

void max_pooling2d(const std::vector<float>& input, std::vector<float>& output,
                const std::array<int, 4>& input_shape, const std::array<int, 4>& output_shape,
                const std::array<int, 2>& pool_size, const std::array<int, 2>& strides,
                const std::string& layer_name) {
    // Extract input dimensions
    int batch_size     = input_shape[0];
    int input_height   = input_shape[1];
    int input_width    = input_shape[2];
    int input_channels = input_shape[3];

    // Extract output dimensions
    int output_height = output_shape[1];
    int output_width  = output_shape[2];

    // Resize output vector to match expected output size
    int output_size = batch_size * output_height * output_width * input_channels;
    output.resize(output_size);

    // Logging layer details
    std::cout << "Performing MaxPooling2D operation for layer: " << layer_name << std::endl;
    std::cout << "Input Shape: (" << input_height << ", " << input_width << ", " << input_channels << ")\n";
    std::cout << "Output Shape: (" << output_height << ", " << output_width << ")\n";
    std::cout << "Pool Size: (" << pool_size[0] << ", " << pool_size[1] << ")\n";
    std::cout << "Strides: (" << strides[0] << ", " << strides[1] << ")\n";
    std::cout << "No padding applied (valid pooling)" << std::endl;

    // Loop over each image in the batch
    for (int batch = 0; batch < batch_size; ++batch) {
        // Loop over the output feature map rows and columns
        for (int row = 0; row < output_height; ++row) {
            for (int col = 0; col < output_width; ++col) {
                // Process each channel independently
                for (int channel = 0; channel < input_channels; ++channel) {
                    float max_val = -std::numeric_limits<float>::infinity();

                    // Loop over the pooling window (filter)
                    for (int pool_row = 0; pool_row < pool_size[0]; ++pool_row) {
                        for (int pool_col = 0; pool_col < pool_size[1]; ++pool_col) {
                            // Calculate the corresponding input indices (valid pooling: no padding)
                            int input_row = row * strides[0] + pool_row;
                            int input_col = col * strides[1] + pool_col;

                            // Only process if within the bounds of the input feature map
                            if (input_row < input_height && input_col < input_width) {
                                int input_idx = ((batch * input_height + input_row) * input_width + input_col) * input_channels + channel;
                                max_val = std::max(max_val, input[input_idx]);
                            }
                        }
                    }

                    // Store the maximum value in the output tensor
                    int output_idx = ((batch * output_height + row) * output_width + col) * input_channels + channel;
                    output[output_idx] = max_val;

                    // Debug print for each output index (optional)
                    // std::cout << "Output Index: " << output_idx << " Value: " << max_val << std::endl;
                }
            }
        }
    }

    std::cout << "MaxPooling2D operation completed for layer: " << layer_name << std::endl;
}
