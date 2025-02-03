// #include "softmax.h"
// #include <cmath>
// #include <iostream>

// void softmax(std::vector<float>& output, const std::string& layer_name) {
//     std::cout << "Applying Softmax activation for layer: " << layer_name << std::endl;
    
//     float sum_exp = 0.0f;
//     for (const auto& value : output) {
//         sum_exp += std::exp(value);
//     }

//     for (auto& value : output) {
//         value = std::exp(value) / sum_exp;
//     }
// }


#include "softmax.h"
#include <cmath>
#include <iostream>
#include <algorithm>  

void softmax(std::vector<float>& output, const std::string& layer_name) {
    std::cout << "Applying Softmax activation for layer: " << layer_name << std::endl;

    float max_value = *std::max_element(output.begin(), output.end());

    float sum_exp = 0.0f;
    for (auto& value : output) {
        value = std::exp(value - max_value); 
        sum_exp += value;
    }

    for (auto& value : output) {
        value /= sum_exp;
    }
}
