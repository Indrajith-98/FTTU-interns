#include "testing.h"
#include <fstream>
#include <vector>
#include <iostream>

bool run_test(const std::string& file1, const std::string& file2,  const std::string& layer_name) {
    std::ifstream bin1(file1, std::ios::binary);
    std::ifstream bin2(file2, std::ios::binary);

    if (!bin1 || !bin2) {
        std::cerr << "Error: Unable to open one or both files!" << std::endl;
        return false;
    }       

    std::vector<char> buffer1((std::istreambuf_iterator<char>(bin1)), std::istreambuf_iterator<char>());
    std::vector<char> buffer2((std::istreambuf_iterator<char>(bin2)), std::istreambuf_iterator<char>());

    size_t min_size = std::min(buffer1.size(), buffer2.size());  
    size_t check_size = min_size * 0.40;  
    size_t correct_count = 0;

    const float tolerance = 1e-3;  

    for (size_t i = 0; i < check_size; i++) {
        float value1 = static_cast<float>(buffer1[i]);
        float value2 = static_cast<float>(buffer2[i]);

        if (std::abs(value1 - value2) < tolerance) {
            correct_count++;
        }
    }

    float accuracy = (float)correct_count / check_size;
    std::cout << "File similarity: " << accuracy * 100 << "% " << "for layer " << layer_name << std::endl;

    return accuracy >= 0.40;  
}



