#include <iostream>
#include "maxpool.h"
#include "file_io.h"
#include "compare.h"

void test_maxpool() {
    std::vector<float> input_data = read_binary_file("../data/input/maxpool_test_input.bin");
    std::vector<float> reference_output = read_binary_file("../data/reference/maxpool_test_output.bin");

    if (input_data.empty() || reference_output.empty()) {
        std::cerr << "❌ ERROR: Missing input or reference output file!" << std::endl;
        return;
    }

    std::vector<float> output_data;
    int input_height = 4, input_width = 4, kernel_size = 2, stride = 2;
    maxpool(input_data, output_data, input_height, input_width, kernel_size, stride);

    bool passed = compare_outputs(output_data, reference_output);
    std::cout << (passed ? "✅ MaxPool Test PASSED!" : "❌ MaxPool Test FAILED!") << std::endl;
}

int main() {
    test_maxpool();
    return 0;
}
