#include "flatten.h"

std::vector<double> Flatten::flatten(const std::vector<std::vector<std::vector<double>>>& input) {
    std::vector<double> output;
    if (input.empty() || input[0].empty() || input[0][0].empty()) {
        return output;
    }
    size_t depth = input.size();
    size_t rows = input[0].size();
    size_t cols = input[0][0].size();
    for (size_t row = 0; row < rows; ++row) {
        for (size_t col= 0; col < cols; ++col) {
            for (size_t d = 0; d < depth; ++d) {
                output.push_back(input[d][row][col]);
            }
        }
    }
    return output;
}
