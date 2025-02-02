#include "utils.h"
#include <iostream>
#include <fstream>

std::vector<float> readBinaryFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open " << filePath << std::endl;
        exit(EXIT_FAILURE);
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<float> buffer(size / sizeof(float));
    file.read(reinterpret_cast<char*>(buffer.data()), size);
    file.close();
    return buffer;
}

void writeBinaryFile(const std::string& filePath, const std::vector<float>& data) {
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open " << filePath << " for writing" << std::endl;
        exit(EXIT_FAILURE);
    }
    file.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(float));
    file.close();
}
