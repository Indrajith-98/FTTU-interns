#include "dense.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

Dense::Dense(const std::vector<double>& input, const std::vector<std::vector<double>>& weights, const std::vector<double>& bias, const std::string& activation)
    : input_(input), weights_(weights), bias_(bias), activation_(activation) {}

std::vector<double> Dense::forward() {
    if (input_.size() != weights_.size()) {
        throw std::invalid_argument("Input size and weights rows must be of the same size");
    }

    std::vector<double> z(weights_[0].size(), 0.0);
    for (size_t i = 0; i < weights_[0].size(); ++i) {
        for (size_t j = 0; j < weights_.size(); ++j) {
            z[i] += (input_[j] * weights_[j][i]);
        }
    }
    
    for (size_t i = 0; i < z.size(); ++i) {
        double y = z[i];
        z[i] += bias_[i];
    }

    return applyActivation(z);
}

std::vector<double> Dense::applyActivation(const std::vector<double>& z) {
    std::vector<double> activated(z.size());

    if (activation_ == "relu") {
        for (size_t i = 0; i < z.size(); ++i) {
            activated[i] = std::max(0.0, z[i]);
        }
    } else if (activation_ == "sigmoid") {
        for (size_t i = 0; i < z.size(); ++i) {
            activated[i] = 1.0 / (1.0 + std::exp(-z[i]));
        }
    } else if (activation_ == "softmax") {
        double max_val = *std::max_element(z.begin(), z.end());
        double sum = 0.0;
        for (const auto& value : z) {
            sum += std::exp(value - max_val);
        }
        for (size_t i = 0; i < z.size(); ++i) {
            activated[i] = std::exp(z[i] - max_val) / sum;
        }
    } else {
        throw std::invalid_argument("Unsupported activation function");
    }

    return activated;
}
