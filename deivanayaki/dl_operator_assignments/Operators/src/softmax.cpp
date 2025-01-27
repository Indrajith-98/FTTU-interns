#include "softmax.h"
#include <cmath>
#include <numeric> // For std::accumulate
#include <algorithm> // For std::max

std::vector<double> Softmax::applySoftmax(const std::vector<double>& logits) {
    // Step 1: Find the maximum value in logits for numerical stability
    double max_logit = *std::max_element(logits.begin(), logits.end());

    // Step 2: Exponentiate each logit after subtracting the max_logit
    std::vector<double> exp_values(logits.size());
    for (size_t i = 0; i < logits.size(); ++i) {
        exp_values[i] = std::exp(logits[i] - max_logit);
    }

    // Step 3: Calculate the sum of all exponentiated values
    double sum_exp_values = std::accumulate(exp_values.begin(), exp_values.end(), 0.0);

    // Step 4: Divide each exponentiated value by the sum to get probabilities
    std::vector<double> probabilities(logits.size());
    for (size_t i = 0; i < exp_values.size(); ++i) {
        probabilities[i] = exp_values[i] / sum_exp_values;
    }

    return probabilities;
}
