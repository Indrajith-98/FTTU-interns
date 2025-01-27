#include "Activation.h"
#include <cmath>
#include <algorithm>

void Activation::relu(std::vector<std::vector<float>>& input) {
    int height = input.size();
    int width = input[0].size();

    // Apply ReLU (set negative values to 0)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            input[i][j] = std::max(0.0f, input[i][j]);  // ReLU operation
        }
    }
}

void Activation::leaky_relu(std::vector<std::vector<float>>& input, float alpha) {
    int height = input.size();
    int width = input[0].size();

    // Apply Leaky ReLU (set negative values to alpha * input)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (input[i][j] < 0) {
                input[i][j] = alpha * input[i][j];  // Leaky part
            }
        }
    }
}

void Activation::sigmoid(std::vector<std::vector<float>>& input) {
    int height = input.size();
    int width = input[0].size();

    // Apply Sigmoid function
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            input[i][j] = 1.0f / (1.0f + std::exp(-input[i][j]));  // Sigmoid operation
        }
    }
}

void Activation::tanh(std::vector<std::vector<float>>& input) {
    int height = input.size();
    int width = input[0].size();

    // Apply Tanh function
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            input[i][j] = std::tanh(input[i][j]);  // Tanh operation
        }
    }
}

void Activation::softmax(std::vector<std::vector<float>>& input) {
    int height = input.size();
    int width = input[0].size();

    // Apply Softmax (usually applied along each row in a classification task)
    for (int i = 0; i < height; ++i) {
        float max_val = *std::max_element(input[i].begin(), input[i].end());  // For numerical stability

        float sum_exp = 0.0f;
        for (int j = 0; j < width; ++j) {
            sum_exp += std::exp(input[i][j] - max_val);  // Exponentiation with numerical stability
        }

        // Normalize to get probabilities
        for (int j = 0; j < width; ++j) {
            input[i][j] = std::exp(input[i][j] - max_val) / sum_exp;  // Softmax formula
        }
    }
}
