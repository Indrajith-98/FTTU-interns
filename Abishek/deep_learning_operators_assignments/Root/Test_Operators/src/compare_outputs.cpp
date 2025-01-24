#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>

std::vector<float> readValuesFromFile(const std::string& file_path) {
    std::vector<float> values;
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << file_path << std::endl;
        return values;
    }
    float value;
    while (file >> value) {
        values.push_back(value);
    }
    file.close();
    return values;
}
bool compareVectors(const std::vector<float>& vec1, const std::vector<float>& vec2, float epsilon = 0.001) {
    if (vec1.size() != vec2.size()) {
        std::cerr << "Vectors have different sizes!" << std::endl;
        return false;
    }
    bool all_equal = true;
    for (size_t i = 0; i < vec1.size(); ++i) {
        bool a = std::fabs(vec1[i] - vec2[i]) > epsilon;
        if (std::fabs(vec1[i] - vec2[i]) > epsilon) {
            std::cerr << "Bool = " << a << std::endl;
            std::cerr << "eps = " << epsilon << std::endl;
            float diff = std::fabs(vec1[i] - vec2[i]);
            std::cerr << diff << std::endl;
            std::cerr << "Difference at index " << i << ": " << vec1[i] << " != " << vec2[i] << std::endl;
            all_equal = false;
            break;
        }
    }
    return all_equal;
}