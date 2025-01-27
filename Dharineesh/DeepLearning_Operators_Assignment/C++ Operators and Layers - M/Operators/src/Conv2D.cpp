
#include "Conv2D.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <chrono>  
#include <iomanip>
#include <cassert>
#include <fstream>

void conv2d(const std::vector<float>& input, const std::vector<float>& kernel,
            const std::vector<float>& bias, std::vector<float>& output,
            const std::array<int, 4>& input_shape, const std::array<int, 4>& output_shape,
            const std::array<int, 2>& kernel_size, const std::array<int, 2>& strides,
            const std::string& padding, const std::string& layer_name) {
    int batch = input_shape[0];
    int input_height = input_shape[1], input_width = input_shape[2], input_channels = input_shape[3];
    int output_height = output_shape[1], output_width = output_shape[2], output_channels = output_shape[3];
    int kernel_height = kernel_size[0], kernel_width = kernel_size[1];
    auto start_time = std::chrono::high_resolution_clock::now();

    for (int b = 0; b < batch; ++b) {
        for (int h = 0; h < output_height; ++h) {
            for (int w = 0; w < output_width; ++w) {
                for (int c = 0; c < output_channels; ++c) {
                    float sum = 0.0f;

                    for (int kh = 0; kh < kernel_height; ++kh) {
                        for (int kw = 0; kw < kernel_width; ++kw) {
                            for (int ic = 0; ic < input_channels; ++ic) {
                                int ih = h * strides[0] + kh;
                                int iw = w * strides[1] + kw;

                                if (padding == "same") {
                                    ih -= kernel_height / 2;
                                    iw -= kernel_width / 2;
                                }

                                if (ih >= 0 && ih < input_height && iw >= 0 && iw < input_width) {
                                    int input_idx = ((b * input_height + ih) * input_width + iw) * input_channels + ic;
                                    int kernel_idx = ((kh * kernel_width + kw) * input_channels + ic) * output_channels + c;

                                    sum += input[input_idx] * kernel[kernel_idx];
                                }
                            }
                        }
                    }

                    int output_idx = ((b * output_height + h) * output_width + w) * output_channels + c;
                    output[output_idx] = std::max(0.0f, sum + bias[c]);
                }
            }
        }
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> execution_time = end_time - start_time;

    std::cout << "\n\n";
    // Print output shape
    std::cout << "Conv2D Output Shape: [" 
         << output_height << ", " 
         << output_width << ", " 
         << output_channels << "]" << std::endl;

    // Print execution time
    std::cout << "Execution Time: " << execution_time.count() << " seconds" << std::endl;

    std::ofstream outfile("O:/C++ Operators and Layers - M/LayerWiseOutput/CppLayerWiseOutput/"+layer_name+".txt");
    if (outfile.is_open()) {
        for (int h = 0; h < output_height; ++h) {
            for (int w = 0; w < output_width; ++w) {
                int output_idx = (h * output_width + w) * output_channels;
                outfile << std::fixed << std::setprecision(6) << output[output_idx] << " ";
            }
            outfile << "\n";
        }
        outfile.close();
        std::cout << "Output of First channel saved to LayerWiseOutput/CppLayerWiseOutput"+layer_name+".txt" << std::endl;
    } else {
        std::cerr << "Error opening file for writing!" << std::endl;
    }
    std::cout << "\n\n";


    std::cout << "Conv2D Output Size = " << output.size() << std::endl;

  
}