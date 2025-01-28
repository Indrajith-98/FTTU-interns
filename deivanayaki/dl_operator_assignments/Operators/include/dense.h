#ifndef DENSE_H
#define DENSE_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath> 

class Dense {
public:
    // Constructor
    Dense(int input_units, int output_units);

    // Method to apply the dense layer transformation
    std::vector<double> applyDenseLayer(const std::vector<double>& input);

    // Setters for weights and biases
    void setWeights(const std::vector<double>& weights);
    void setBiases(const std::vector<double>& biases);

private:
    int input_units;  // Number of input features
    int output_units; // Number of neurons in the dense layer

    std::vector<double> weights;  // Flattened weights for the dense layer
    std::vector<double> biases;   // Biases for the dense layer
};

#endif  // DENSE_H
