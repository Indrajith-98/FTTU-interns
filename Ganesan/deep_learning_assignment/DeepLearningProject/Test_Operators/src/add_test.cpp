#include <iostream>
#include "add.h"
#include "file_io.h"
#include "compare.h"

void test_add() {
    std::vector<float> input_data1 = read_binary_file("../data/input/add_test_input1.bin");
    std::vector<float> input_data2 = read_binary_file("../data/input/add_test_input2.bin");
    std::vector<float> reference_output = read_binary_file("../data/reference/add_test_output.bin");

    if (input_data1.empty() || input_data2.empty() || reference_output.empty()) {
        std::cerr << "❌ ERROR: Missing input or reference output file!" << std::endl;
        return;
    }

    std::vector<float> output_data;
    Add addLayer;
    output_data = addLayer.forward(input_data1, input_data2);

    bool passed = compare_outputs(output_data, reference_output);
    std::cout << (passed ? "✅ Add Test PASSED!" : "❌ Add Test FAILED!") << std::endl;
}

int main() {
    test_add();
    return 0;
}
