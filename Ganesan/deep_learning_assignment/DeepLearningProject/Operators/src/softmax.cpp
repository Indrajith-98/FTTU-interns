#include "softmax.h"
#include <cmath>
#include <algorithm>

void softmax(const std::vector<float>& input_data, std::vector<float>& output_data) {
    float max_val = *std::max_element(input_data.begin(), input_data.end());

    std::vector<float> exp_values(input_data.size());
    float sum_exp = 0.0;
    for (size_t i = 0; i < input_data.size(); ++i) {
        exp_values[i] = std::exp(input_data[i] - max_val);
        sum_exp += exp_values[i];
    }

    output_data.resize(input_data.size());
    for (size_t i = 0; i < input_data.size(); ++i) {
        output_data[i] = exp_values[i] / sum_exp;
    }
}
