#include "relu.h"
#include <iostream>

void relu(std::vector<float>& input_output, const std::string& layer_name) {
    std::cout << "Applying ReLU activation for layer: " << layer_name << std::endl;
    
    for (auto& value : input_output) {
        value = std::max(0.0f, value); 
    }
}
