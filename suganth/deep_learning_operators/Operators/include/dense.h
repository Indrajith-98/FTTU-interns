#ifndef DENSE_H
#define DENSE_H

#include <vector>
#include <string>

class Dense {
public:
    Dense(const std::vector<double>& input, const std::vector<std::vector<double>>& weights, const std::vector<double>& bias, const std::string& activation);

    // Method to perform the forward pass
    std::vector<double> forward();

private:
    std::vector<double> input_;
    std::vector<std::vector<double>> weights_;
    std::vector<double> bias_;
    std::string activation_;

    // Method to apply the activation function
    std::vector<double> applyActivation(const std::vector<double>& z);
};

#endif // DENSE_H