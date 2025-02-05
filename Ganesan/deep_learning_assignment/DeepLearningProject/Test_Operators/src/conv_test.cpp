#include <iostream>
#include "conv.h"
#include "file_io.h"
#include "compare.h"

void test_convolution() {
    std::vector<float> input_data = read_binary_file("../data/input/conv_test_input.bin");
    std::vector<float> reference_output = read_binary_file("../data/reference/conv_test_output.bin");

    if (input_data.empty() || reference_output.empty()) {
        std::cerr << "❌ ERROR: Missing input or reference output file!" << std::endl;
        return;
    }


    int input_size = 32, stride = 1, padding = 1, kernel_size = 3;
    int output_size = input_size - kernel_size + 2 * padding + 1;
    output.resize(output_size * output_size);

    std::vector<float> weights(kernel_size * kernel_size, 0.00000001);
    std::vector<float> output_data;

    conv(input_data, weights, output_data, input_size, stride, padding, kernel_size);

    bool passed = compare_outputs(output_data, reference_output);
    std::cout << (passed ? "✅ Convolution Test PASSED!" : "❌ Convolution Test FAILED!") << std::endl;
}

int main() {
    test_convolution();
    return 0;
}
