

#include "MaxPooling2D.h"
#include <iostream>
#include <cmath>
#include <limits>
#include <chrono>  
#include <fstream>
#include <iomanip>

void max_pooling2d(const std::vector<float>& input, std::vector<float>& output,
                   const std::array<int, 4>& input_shape, const std::array<int, 4>& output_shape,
                   const std::array<int, 2>& pool_size, const std::array<int, 2>& strides,
                   const std::string& padding, const std::string& layer_name) {
    int batch = input_shape[0];
    int in_height = input_shape[1], in_width = input_shape[2], in_channels = input_shape[3];
    int out_height = output_shape[1], out_width = output_shape[2];

    int pad_height = 0, pad_width = 0;

    if (padding == "same") {
        // Calculate padding based on "same" padding rule
        pad_height = std::max(0, (out_height - 1) * strides[0] + pool_size[0] - in_height);
        pad_width = std::max(0, (out_width - 1) * strides[1] + pool_size[1] - in_width);
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    
    for (int b = 0; b < batch; ++b) {
        for (int h = 0; h < out_height; ++h) {
            for (int w = 0; w < out_width; ++w) {
                for (int c = 0; c < in_channels; ++c) {
                    float max_val = -std::numeric_limits<float>::infinity();

                    for (int ph = 0; ph < pool_size[0]; ++ph) {
                        for (int pw = 0; pw < pool_size[1]; ++pw) {
                            // For "valid" padding, no need to adjust indices, just ensure within bounds
                            int ih = h * strides[0] + ph;
                            int iw = w * strides[1] + pw;

                            if (ih >= 0 && ih < in_height && iw >= 0 && iw < in_width) {
                                int input_idx = ((b * in_height + ih) * in_width + iw) * in_channels + c;
                                max_val = std::max(max_val, input[input_idx]);
                            }
                        }
                    }

                    int output_idx = ((b * out_height + h) * out_width + w) * in_channels + c;
                    output[output_idx] = max_val;
                }
            }
        }
    }
    auto end_time = std::chrono::high_resolution_clock::now();

     std::chrono::duration<double> execution_time = end_time - start_time;
    
    std::cout << "\n\n";

    // Prepare to save the first channel to a text file
    std::ofstream outfile("O:/C++ Operators and Layers - M/LayerWiseOutput/CppLayerWiseOutput/"+layer_name+".txt");
    if (!outfile.is_open()) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    for (int h = 0; h < out_height; ++h) {
        for (int w = 0; w < out_width; ++w) {
            int output_idx = ((0 * out_height + h) * out_width + w) * in_channels;

            outfile << output[output_idx] << " ";  // Write to file
        }
        // std::cout << std::endl;
        outfile << std::endl;
    }
    outfile.close();

    // Print output shape and execution time
    std::cout << "MaxPooling2D Output Shape: [" << batch << ", " << out_height << ", " << out_width << ", " << input_shape[3] << "]" << std::endl;
    std::cout << "MaxPooling2D Execution Time: " << execution_time.count() << " seconds" << std::endl;
    std::cout << "Output of First channel saved to LayerWiseOutput/CppLayerWiseOutput"+layer_name+".txt" << std::endl;
    std::cout << "\n\n";
}
