#include <iostream>
#include "matmul.h"
#include "file_io.h"
#include "compare.h"

void test_matmul() {
    std::vector<float> input_data = read_binary_file("../data/input/matmul_test_input.bin");
    std::vector<float> weights = read_binary_file("../data/input/matmul_test_weights.bin");
    std::vector<float> bias = read_binary_file("../data/input/matmul_test_bias.bin");
    std::vector<float> reference_output = read_binary_file("../data/reference/matmul_test_output.bin");

    if (input_data.empty() || weights.empty() || bias.empty() || reference_output.empty()) {
        std::cerr << "❌ ERROR: Missing input, weights, bias, or reference output file!" << std::endl;
        return;
    }

    int input_size = input_data.size();
    int output_size = bias.size();

    std::vector<float> output_data;
    MatMul matmulLayer;
    output_data = matmulLayer.forward(input_data, weights, bias, input_size, output_size);

    bool passed = compare_outputs(output_data, reference_output);
    std::cout << (passed ? "✅ MatMul Test PASSED!" : "❌ MatMul Test FAILED!") << std::endl;
}

int main() {
    test_matmul();
    return 0;
}
