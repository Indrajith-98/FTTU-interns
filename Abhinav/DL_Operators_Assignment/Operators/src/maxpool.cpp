#include "maxpool.h"
#include <iostream>
#include <fstream>

MaxPooling2D::MaxPooling2D(int pool_size) : poolSize(pool_size) {}

void MaxPooling2D::forward(const std::string& inputPath, const std::string& outputPath) {
    std::cout << "Applying MaxPooling2D with pool size: " << poolSize << std::endl;

    std::ifstream inputFile(inputPath, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error: Cannot open input file " << inputPath << std::endl;
        return;
    }

    int rows, cols;
    inputFile.read(reinterpret_cast<char*>(&rows), sizeof(int));
    inputFile.read(reinterpret_cast<char*>(&cols), sizeof(int));

    std::vector<std::vector<float>> input(rows, std::vector<float>(cols));
    for (int i = 0; i < rows; ++i) {
        inputFile.read(reinterpret_cast<char*>(input[i].data()), cols * sizeof(float));
    }
    inputFile.close();

    // Apply pooling
    std::vector<std::vector<float>> output = applyPooling(input);

    std::ofstream outputFile(outputPath, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Error: Cannot open output file " << outputPath << std::endl;
        return;
    }

    int new_rows = static_cast<int>(output.size());  // Fixed warning
    int new_cols = static_cast<int>(output[0].size());  // Fixed warning
    outputFile.write(reinterpret_cast<const char*>(&new_rows), sizeof(int));
    outputFile.write(reinterpret_cast<const char*>(&new_cols), sizeof(int));

    for (const auto& row : output) {
        outputFile.write(reinterpret_cast<const char*>(row.data()), new_cols * sizeof(float));
    }
    outputFile.close();
}

std::vector<std::vector<float>> MaxPooling2D::applyPooling(const std::vector<std::vector<float>>& input) {
    int rows = static_cast<int>(input.size());  // Fixed warning
    int cols = static_cast<int>(input[0].size());  // Fixed warning
    int new_rows = rows / poolSize;
    int new_cols = cols / poolSize;

    std::vector<std::vector<float>> output(new_rows, std::vector<float>(new_cols, 0));

    for (int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < new_cols; ++j) {
            float max_val = -1e9;
            for (int x = 0; x < poolSize; ++x) {
                for (int y = 0; y < poolSize; ++y) {
                    max_val = std::max(max_val, input[i * poolSize + x][j * poolSize + y]);
                }
            }
            output[i][j] = max_val;
        }
    }
    return output;
}
