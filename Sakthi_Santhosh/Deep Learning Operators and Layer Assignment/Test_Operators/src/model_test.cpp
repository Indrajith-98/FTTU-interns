#include "model_test.h"

std::vector<float> parseLine(const std::string &line) {
    std::vector<float> values;
    std::stringstream ss(line);
    float val;
    while (ss >> val) {
        values.push_back(val);
    }
    return values;
}

std::vector<int> getLargestValueIndices(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        exit(1);
    }

    std::vector<int> largest_value_indices;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<float> values = parseLine(line);
        if (values.size() == 10) {  // Ensure the line contains exactly 10 values
            auto max_iter = std::max_element(values.begin(), values.end());
            int max_index = std::distance(values.begin(), max_iter);
            largest_value_indices.push_back(max_index);
        }
    }
    
    return largest_value_indices;
}

bool compareResults(const std::vector<int> &result1, const std::vector<int> &result2) {
    if (result1.size() != result2.size()) {
        std::cerr << "Error: Results size mismatch!" << std::endl;
        return false;
    }

    for (size_t i = 0; i < result1.size(); ++i) {
        if (result1[i] != result2[i]) {
            std::cerr << "Mismatch at index " << i << ": " << result1[i] << " vs " << result2[i] << std::endl;
            return false;
        }
    }
    
    return true;
}