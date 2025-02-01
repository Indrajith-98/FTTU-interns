#include "flatten.h"
#include <iostream>
#include <cassert>

// Flatten operation: Reshape a multi-dimensional input (e.g., 4D tensor) to a 1D vector
void flatten(const std::vector<float>& input, const std::array<int, 4>& input_shape, std::vector<float>& output) {
    int total_elements = input_shape[0] * input_shape[1] * input_shape[2] * input_shape[3];
    output.resize(total_elements);

    for (int i = 0; i < total_elements; ++i) {
        output[i] = input[i];
    }

    std::cout << "Flattening (4D) completed. Output size: " << output.size() << std::endl;
}
