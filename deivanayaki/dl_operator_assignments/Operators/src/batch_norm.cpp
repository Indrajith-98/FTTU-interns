#include "batch_norm.h"
#include <cmath>
#include <stdexcept>

// Constructor to initialize batch normalization parameters
BatchNorm::BatchNorm(
    const std::vector<double>& gamma,
    const std::vector<double>& beta,
    const std::vector<double>& moving_mean,
    const std::vector<double>& moving_variance,
    float epsilon)
    : gamma_(gamma), beta_(beta), moving_mean_(moving_mean),
      moving_variance_(moving_variance), epsilon_(epsilon) {
    if (gamma_.size() != beta_.size() || gamma_.size() != moving_mean_.size() ||
        gamma_.size() != moving_variance_.size()) {
        throw std::runtime_error("BatchNorm parameter dimensions mismatch.");
    }
}

// Apply batch normalization to the feature map
std::vector<std::vector<std::vector<double>>> BatchNorm::applyBatchNorm(
    const std::vector<std::vector<std::vector<double>>>& feature_map) {
    size_t height = feature_map.size();
    size_t width = feature_map[0].size();
    size_t channels = feature_map[0][0].size();

    if (channels != gamma_.size()) {
        throw std::runtime_error("Feature map channels do not match BatchNorm parameters.");
    }

    // Output feature map with same dimensions as input
    std::vector<std::vector<std::vector<double>>> normalized_map(height,
        std::vector<std::vector<double>>(width, std::vector<double>(channels, 0.0)));

    // Normalize each channel
    for (size_t c = 0; c < channels; ++c) {
        for (size_t h = 0; h < height; ++h) {
            for (size_t w = 0; w < width; ++w) {
                double normalized = (feature_map[h][w][c] - moving_mean_[c]) /
                                   std::sqrt(moving_variance_[c] + epsilon_);
                normalized_map[h][w][c] = (gamma_[c] * normalized) + beta_[c];
            }
        }
    }

    return normalized_map;
}

std::vector<double> BatchNorm::applyBatchNorm(const std::vector<double>& dense_output) {
    size_t size = dense_output.size();
    if (size != gamma_.size()) {
        throw std::runtime_error("Dense layer output size does not match BatchNorm parameters.");
    }

    // Output vector with the same size as input
    std::vector<double> normalized_output(size, 0.0);

    // Normalize each unit
    for (size_t i = 0; i < size; ++i) {
        double normalized = (dense_output[i] - moving_mean_[i]) / std::sqrt(moving_variance_[i] + epsilon_);
        normalized_output[i] = (gamma_[i] * normalized) + beta_[i];
    }

    return normalized_output;
}