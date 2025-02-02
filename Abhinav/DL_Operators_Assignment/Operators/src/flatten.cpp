#include "flatten.h"
#include <iostream>
#include <fstream>

Flatten::Flatten() {}

void Flatten::forward(const std::string& inputPath, const std::string& outputPath) {
    std::cout << "Flattening input tensor from: " << inputPath << " to " << outputPath << std::endl;

    std::ifstream inputFile(inputPath, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error: Cannot open input file " << inputPath << std::endl;
        return;
    }

    int depth, rows, cols;
    inputFile.read(reinterpret_cast<char*>(&depth), sizeof(int));
    inputFile.read(reinterpret_cast<char*>(&rows), sizeof(int));
    inputFile.read(reinterpret_cast<char*>(&cols), sizeof(int));

    std::vector<std::vector<std::vector<float>>> input(
        static_cast<size_t>(depth),
        std::vector<std::vector<float>>(static_cast<size_t>(rows), std::vector<float>(static_cast<size_t>(cols)))
    );

    for (int d = 0; d < depth; ++d) {
        for (int i = 0; i < rows; ++i) {
            inputFile.read(reinterpret_cast<char*>(input[d][i].data()), cols * sizeof(float));
        }
    }
    inputFile.close();

    std::vector<float> output = flattenData(input);

    std::ofstream outputFile(outputPath, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Error: Cannot open output file " << outputPath << std::endl;
        return;
    }

    int flat_size = static_cast<int>(output.size());  // Fixed warning
    outputFile.write(reinterpret_cast<const char*>(&flat_size), sizeof(int));
    outputFile.write(reinterpret_cast<const char*>(output.data()), flat_size * sizeof(float));
    outputFile.close();
}

std::vector<float> Flatten::flattenData(const std::vector<std::vector<std::vector<float>>>& input) {
    std::vector<float> output;
    for (const auto& matrix : input) {
        for (const auto& row : matrix) {
            for (float val : row) {
                output.push_back(val);
            }
        }
    }
    return output;
}
