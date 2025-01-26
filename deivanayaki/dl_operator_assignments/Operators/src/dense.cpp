#include "dense.h"

// Constructor: Initializes input and output sizes
Dense::Dense(int input_units, int output_units)
    : input_units(input_units), output_units(output_units) {}

// Apply the Dense layer transformation: input * weights + biases
std::vector<double> Dense::applyDenseLayer(const std::vector<double>& input) {
    // Check if input size matches the expected size
    if (input.size() != input_units) {
        throw std::invalid_argument("Input size does not match expected input units.");
    }

    std::vector<double> output(output_units, 0.0);

    // Access weights in a row-major order as in Python
    for (int i = 0; i < input_units; ++i) {
        for (int j = 0; j < output_units; ++j) {
            int weight_index = i * output_units + j;
            output[j] += input[i] * weights[weight_index];
        }
    }

    // Add biases
    for (int j = 0; j < output_units; ++j) {
        output[j] += biases[j];
    }

    return output;
}

// Setter for weights (flattened 1D vector)
void Dense::setWeights(const std::vector<double>& weights) {

    if (weights.size() != input_units * output_units) {
        throw std::invalid_argument("Weights vector size does not match input and output units.");
    }
    this->weights = weights;
}

// Setter for biases
void Dense::setBiases(const std::vector<double>& biases) {
    if (biases.size() != output_units) {
        throw std::invalid_argument("Biases vector size does not match output size.");
    }
    this->biases = biases;
}
