#include "max_pool.h"

// Constructor
MaxPool::MaxPool(std::vector<int> pool_size, std::vector<int> strides)
    : pool_size(pool_size), strides(strides) {}

// Apply max pooling on the input feature map
std::vector<std::vector<std::vector<double>>> MaxPool::applyMaxPool(
    const std::vector<std::vector<std::vector<double>>>& input_map) {

    int input_height = input_map.size();
    int input_width = input_map[0].size();
    int channels = input_map[0][0].size();

    int output_height = (input_height - pool_size[0]) / strides[0] + 1;
    int output_width = (input_width - pool_size[1]) / strides[1] + 1;
    
    std::vector<std::vector<std::vector<double>>> pooled_map(
        output_height, std::vector<std::vector<double>>(
            output_width, std::vector<double>(channels, 0)));

    // Perform max pooling
    for (int h = 0; h < output_height; ++h) {
        for (int w = 0; w < output_width; ++w) {
            for (int c = 0; c < channels; ++c) {
                int start_h = h * strides[0];
                int start_w = w * strides[1];
                int end_h = start_h + pool_size[0];
                int end_w = start_w + pool_size[1];

                double max_value = -std::numeric_limits<double>::infinity();
                for (int i = start_h; i < end_h; ++i) {
                    for (int j = start_w; j < end_w; ++j) {
                        max_value = std::max(max_value, input_map[i][j][c]);
                    }
                }
                pooled_map[h][w][c] = max_value;
            }
        }
    }

    return pooled_map;
}