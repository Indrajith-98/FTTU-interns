#include <iostream>
#include "relu.h"
#include "file_io.h"
#include "compare.h"

void test_relu() {
    std::vector<float> input_data = read_binary_file("../data/input/relu_test_input.bin");
    std::vector<float> reference_output = read_binary_file("../data/reference/relu_test_output.bin");

    if (input_data.empty() || reference_output.empty()) {
        std::cerr << "❌ ERROR: Missing input or reference output file!" << std::endl;
        return;
    }

    std::vector<float> output_data;
    relu(input_data, output_data);

    bool passed = compare_outputs(output_data, reference_output);
    std::cout << (passed ? "✅ ReLU Test PASSED!" : "❌ ReLU Test FAILED!") << std::endl;
}

int main() {
    test_relu();
    return 0;
}
