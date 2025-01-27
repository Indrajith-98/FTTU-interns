#include "selu.h"
#include <cmath>  // for exp() function

// Constructor to initialize the constants
SELU::SELU(double lambda, double alpha) : lambda(lambda), alpha(alpha) {}

// Method to apply the SELU activation to a vector of inputs
std::vector<double> SELU::apply(const std::vector<double>& input) {
    std::vector<double> output;
    output.reserve(input.size());

    for (double val : input) {
        if (val > 0) {
            output.push_back(lambda * val);  // Apply scaling for positive values
        } else {
            output.push_back(lambda * alpha * (std::exp(val) - 1));  // Apply scaled exponential for negative values
        }
    }

    return output;
}
