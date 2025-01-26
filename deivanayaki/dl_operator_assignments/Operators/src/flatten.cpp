#include "flatten.h"

// Flatten the 3D feature map into a 1D vector
std::vector<double> Flatten::flatten(const std::vector<std::vector<std::vector<double>>>& input_map) {

    // Get dimensions of input map
    int height = input_map.size();
    int width = input_map[0].size();
    int channels = input_map[0][0].size();

    std::vector<double> flattened_map(height * width * channels);
    int index = 0;
    for (int h = 0; h < height; ++h) {
        for (int w = 0; w < width; ++w) {
            for (int c = 0; c < channels; ++c) {
                flattened_map[index++] = input_map[h][w][c];
            }
        }
    }

    return flattened_map;
}
