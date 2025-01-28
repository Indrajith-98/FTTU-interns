#ifndef SOFTMAX_H
#define SOFTMAX_H

#include <vector>

class Softmax {
public:
    // Constructor (optional if parameters are dynamic)
    Softmax() = default;

    // Method to apply the softmax function
    std::vector<double> applySoftmax(const std::vector<double>& logits);
};

#endif // SOFTMAX_H
