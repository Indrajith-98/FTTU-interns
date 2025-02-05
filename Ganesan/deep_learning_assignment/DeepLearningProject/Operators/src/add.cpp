#include "add.h"

// Constructor
Add::Add() {
    std::cout << "✅ Add Layer Initialized." << std::endl;
}

// Perform element-wise addition
std::vector<float> Add::forward(const std::vector<float>& input1, const std::vector<float>& input2) {
    if (input1.size() != input2.size()) {
        std::cerr << "❌ Error: Input sizes do not match for Add operation!" << std::endl;
        return {};
    }

    std::vector<float> output(input1.size());
    for (size_t i = 0; i < input1.size(); ++i) {
        output[i] = input1[i] + input2[i];
    }

    // Debug Output
    std::cout << "🔹 Add Output (First 5 values): ";
    for (size_t i = 0; i < std::min(size_t(5), output.size()); ++i) {
        std::cout << output[i] << " ";
    }
    std::cout << std::endl;

    return output;
}

// Destructor
Add::~Add() {
    std::cout << "🛑 Add Layer Destroyed." << std::endl;
}
