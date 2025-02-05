#include <iostream>
#include "softmax.h"
#include "file_io.h"
#include "compare.h"

void test_softmax() {
    std::vector<float> input_data = read_binary_file("../data/input/softmax_test_input.bin");
    std::vector<float> reference_output = read_binary_file("../data/reference/softmax_test_output.bin");

    if (input_data.empty() || reference_output.empty()) {
        std::cerr << "❌ ERROR: Missing input or reference output file!" << std::endl;
        return;
    }

    std::vector<float> output_data;
    softmax(input_data, output_data);

    bool passed = compare_outputs(output_data, reference_output);
    std::cout << (passed ? "✅ Softmax Test PASSED!" : "❌ Softmax Test FAILED!") << std::endl;
}

int main() {
    test_softmax();
    return 0;
}
