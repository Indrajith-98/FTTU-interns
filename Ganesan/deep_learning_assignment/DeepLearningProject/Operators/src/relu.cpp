#include "relu.h"
#include <algorithm> 

void relu(const std::vector<float>& input_data, std::vector<float>& output_data) {
    output_data.resize(input_data.size());
    for (size_t i = 0; i < input_data.size(); ++i) {
        output_data[i] = std::max(0.0f, input_data[i]);
    }
}
