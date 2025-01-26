#include "prelu.h"
#include <iostream>

// Constructor to initialize alpha values (for each channel)
PReLU::PReLU(const std::vector<std::vector<std::vector<double>>>& alpha_values)
    : alpha_values_(alpha_values) {
}

std::vector<std::vector<std::vector<double>>> PReLU::applyPReLU(
    std::vector<std::vector<std::vector<double>>>& feature_map) {
    size_t height = feature_map.size();
    size_t width = feature_map[0].size();
    size_t channels = feature_map[0][0].size();

    // Ensure alpha_values_ has matching dimensions (30 x 30 x 64)
    if (alpha_values_.size() != height || alpha_values_[0].size() != width || alpha_values_[0][0].size() != channels) {
        throw std::runtime_error("Alpha dimensions do not match feature map dimensions.");
    }

    // Apply PReLU activation
    for (size_t h = 0; h < height; ++h) {
        for (size_t w = 0; w < width; ++w) {
            for (size_t c = 0; c < channels; ++c) {
                if (feature_map[h][w][c] < 0) {
                    feature_map[h][w][c] *= alpha_values_[h][w][c]; // Scale by alpha if negative
                }
            }
        }
    }

    return feature_map;
}

