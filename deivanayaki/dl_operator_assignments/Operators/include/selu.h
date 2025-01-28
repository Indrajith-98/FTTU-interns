#ifndef SELU_H
#define SELU_H

#include <vector>

class SELU {
public:
    // Constructor that can be used for initializing the constants (alpha and lambda)
    SELU(double lambda = 1.0507, double alpha = 1.6733);

    // Method to apply the SELU activation function to a vector of inputs
    std::vector<double> apply(const std::vector<double>& input);

private:
    double lambda;  // Lambda constant (Scaling factor)
    double alpha;   // Alpha constant (Leaky factor for negative values)
};

#endif // SELU_H
