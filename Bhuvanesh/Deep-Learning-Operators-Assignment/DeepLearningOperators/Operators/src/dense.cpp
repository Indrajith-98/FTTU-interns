#include "dense.h"
#include "relu.h"
#include "softmax.h"
#include <cmath>

void dense(const std::vector<float>& input, const std::vector<float>& weights,
           const std::vector<float>& bias, std::vector<float>& output,
           const std::array<int, 1>& input_shape, const std::array<int, 1>& output_shape,
           const std::string& activation, const std::string& layer_name) {
    int in_units = input_shape[0];
    int out_units = output_shape[0];

    assert(input.size() == in_units);
    assert(weights.size() == in_units * out_units);
    assert(bias.size() == out_units);
    assert(output.size() == out_units);

    std::cout << "Performing Dense operation for layer: " << layer_name << std::endl;

    for (int i = 0; i < out_units; ++i) {
        float sum = 0.0f;
        for (int j = 0; j < in_units; ++j) {
            sum += input[j] * weights[i * in_units + j];
        }
        sum += bias[i];

        output[i] = sum;
        
    }

    if (activation == "relu") {
        relu(output, layer_name);  
    } else if (activation == "softmax") {
        softmax(output, layer_name);
    } 
}
