#include "unit_test.h"
#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

// Open the result file for appending results
std::ofstream result_file("O:/C++ Operators and Layers - M/report/unit_test.txt", std::ios::app);

// Utility function to read a file into a 1D vector
std::vector<float> read_file_to_vector(const std::string& file_path) {
    std::vector<float> data;
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << file_path << std::endl;
        return {};
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        float value;
        while (iss >> value) {
            data.push_back(value);
        }
    }

    file.close();
    return data;
}

// Unit test function with improved precision handling
void unit_test(const std::string& layer, const std::string& output_file, const std::string& expected_file, float epsilon) {
    auto output_data = read_file_to_vector(output_file);
    auto expected_data = read_file_to_vector(expected_file);

    if (output_data.size() != expected_data.size()) {
        std::cerr << "Test Failed: Size mismatch between output (" << output_data.size() 
                  << ") and expected (" << expected_data.size() << ") data." << std::endl;
        result_file << layer << " Test Failed: Size mismatch." << std::endl;
        return;
    }

    bool test_passed = true;
    size_t mismatch_count = 0;

    for (size_t i = 0; i < output_data.size(); ++i) {
        if (std::abs(output_data[i] - expected_data[i]) > epsilon) {
            std::cerr << std::fixed << std::setprecision(5); // Set precision for debugging output
            std::cerr << "Mismatch at index " << i << ": output = " << output_data[i]
                      << ", expected = " << expected_data[i] << std::endl;
            mismatch_count++;
            test_passed = false;
        }
    }

    if (test_passed) {
        result_file << layer << " Test Passed: All values match within tolerance (" << epsilon << ")." << std::endl;
        std::cout << layer << " Test Passed: All values match within tolerance (" << epsilon << ")." << std::endl;
    } else {
        result_file << layer << " Test Failed: " << mismatch_count 
                    << " mismatched values found exceeding tolerance (" << epsilon << ")." << std::endl;
        std::cerr << layer << " Test Failed: " << mismatch_count 
                  << " mismatched values found exceeding tolerance (" << epsilon << ")." << std::endl;
    }
}
