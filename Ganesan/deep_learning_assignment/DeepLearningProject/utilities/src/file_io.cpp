#include "file_io.h"
#include <fstream>
#include <iostream>

std::vector<float> read_binary_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "❌ Error: Failed to open " << filename << std::endl;
        return {};
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg() / sizeof(float);
    file.seekg(0, std::ios::beg);

    std::vector<float> data(size);
    file.read(reinterpret_cast<char*>(data.data()), size * sizeof(float));
    return data;
}

void write_binary_file(const std::string& filename, const std::vector<float>& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "❌ Error: Failed to open " << filename << std::endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(float));
}
