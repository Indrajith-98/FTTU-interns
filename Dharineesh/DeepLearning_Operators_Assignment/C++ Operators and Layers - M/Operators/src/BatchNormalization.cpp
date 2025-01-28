#include "BatchNormalization.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <chrono>  
#include <iomanip>
#include <string>
#include <cassert>


// Function to perform batch normalization
void batch_normalization(const std::vector<float>& input, std::vector<float>& output,
                         const std::vector<float>& gamma, const std::vector<float>& beta,
                         const std::vector<float>& moving_mean, const std::vector<float>& moving_variance,
                         float epsilon, size_t channels, size_t height, size_t width, const std::string& layer_name) {
                            
    // Validate input sizes
    std::cout << channels * height * width <<"\n";
    std::cout << input.size() <<"\n";  

    // Resize output to match input size
    output.resize(input.size());
    auto start_time = std::chrono::high_resolution_clock::now();

    // Perform batch normalization
    for (size_t c = 0; c < channels; ++c) {
        for (size_t h = 0; h < height; ++h) {
            for (size_t w = 0; w < width; ++w) {
                // Calculate the index based on the assumed data format
                size_t idx = (h * width + w) * channels + c;
                assert(idx < input.size());

                // Apply batch normalization formula
                output[idx] = gamma[c] * (input[idx] - moving_mean[c]) /
                              std::sqrt(moving_variance[c] + epsilon) + beta[c];
            }
        }
    }
    auto end_time = std::chrono::high_resolution_clock::now();

     std::chrono::duration<double> execution_time = end_time - start_time;

    std::cout << "\n\n";

    // Print execution time
    std::cout << "Execution time for batch_normalization_1d: " << execution_time.count() << " seconds\n";

    // Save the first channel to a text file
    std::ofstream outfile("O:/C++ Operators and Layers - M/LayerWiseOutput/CppLayerWiseOutput/"+layer_name+".txt");
    if (!outfile.is_open()) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    // Debug output for the first channel
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = (y * width + x) * channels;
            outfile << output[idx] << " "; // Write to file
        }
        // std::cout << "\n";
        outfile << "\n";
    }
    outfile.close();
    std::cout << "Output of First channel saved to LayerWiseOutput/CppLayerWiseOutput"+layer_name+".txt" << std::endl;
    std::cout << "\n\n";

    // Output the size of the result for verification
    std::cout << "BatchNormalization Output Size = " << output.size() << std::endl;
}