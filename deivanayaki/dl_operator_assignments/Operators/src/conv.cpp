#include "conv.h"
#include "../../utils/include/LogUtils.h"
#include "../../Test_Operators/include/conv_test.h"

void ConvLayer::setAttributes(int filters, const std::vector<int>& input_shape, const std::vector<int>& output_shape, 
                               const std::vector<int>& kernel_size, const std::vector<int>& strides, const std::string& padding, 
                               const std::vector<int>& weights_shape, const std::vector<double>& weights, const std::vector<double>& biases) {
    this->filters = filters;
    this->input_shape = input_shape;
    this->output_shape = output_shape;
    this->kernel_size = kernel_size;
    this->strides = strides;
    this->padding = padding;
    this->weights_shape = weights_shape;
    this->weights = weights;
    this->biases = biases;
}

std::vector<std::vector<std::vector<double>>> ConvLayer::convolve(const std::vector<std::vector<std::vector<double>>>& input) const {
    // Ensure padding is set to "valid" (no additional padding added)
    if (padding != "valid") {
        throw std::invalid_argument("Only 'valid' padding is supported in this implementation.");
    }

    // Input dimensions
    int input_height = input_shape[1];
    int input_width = input_shape[2];
    int input_channels = input_shape[3];

    // Kernel dimensions
    int kernel_height = kernel_size[0];
    int kernel_width = kernel_size[1];

    // Strides
    int stride_y = strides[0];
    int stride_x = strides[1];

    // Output dimensions (already set in output_shape)
    int output_height = (input_height - kernel_height) / stride_y + 1;
    int output_width = (input_width - kernel_width) / stride_x + 1;
    int output_depth = filters;

    // Unit Test to ensure correct output shape.
    ConvTest :: checkOutputShape(output_shape, output_height, output_width, output_depth);
    unitTestLogExecution("Conv Layer output shape verified");

    // Initialize output feature map
    std::vector<std::vector<std::vector<double>>> output(output_height,
        std::vector<std::vector<double>>(output_width, std::vector<double>(output_depth, 0.0)));

    // Convolution operation
    for (int f = 0; f < filters; ++f) { // Loop over filters
        for (int y_out = 0; y_out < output_height; ++y_out) { // Loop over output height
            for (int x_out = 0; x_out < output_width; ++x_out) { // Loop over output width
                double value = 0.0f;
                for (int c = 0; c < input_channels; ++c) { // Loop over input channels
                    for (int ky = 0; ky < kernel_height; ++ky) { // Loop over kernel height
                        for (int kx = 0; kx < kernel_width; ++kx) { // Loop over kernel width
                            // Compute the input coordinates
                            int in_y = y_out * stride_y + ky;
                            int in_x = x_out * stride_x + kx;

                            // Ensure indices are within bounds (for valid padding)
                            if (in_y < input_height && in_x < input_width) {
                                // Compute weight index and accumulate result
                                int weight_index = (((ky * kernel_width + kx) * input_channels + c) * filters + f);
                                value += input[in_y][in_x][c] * weights[weight_index];
                            }
                        }
                    }
                }
                // Add bias
                value += biases[f];
                output[y_out][x_out][f] = value;
            }
        }
    }
    return output;
}
