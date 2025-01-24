#include <iostream>

#include "utility.h"

std::vector<std::vector<float>> Utility::createGaussianKernel(int size, float sigma)
{
    if (size % 2 == 0) {
        std::cout << "[ERROR] Kernel size must be odd.\n";
        return {};
    }

    std::vector<std::vector<float>> kernel(size, std::vector<float>(size, 0.0f));
    const int center = size / 2;
    float sum = 0.0f;

    // e^2(-(x^2 + y^2)/(2(sigma)^2)) - calculating the non-nomalized kernel and normalizing the kernel later based on the actual sum to perform better normalization
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int x = i - center;
            int y = j - center;
            float exponent = -(x * x + y * y) / (2.0f * sigma * sigma);
            kernel[i][j] = exp(exponent);
            sum += kernel[i][j];
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            kernel[i][j] /= sum;
        }
    }

    return kernel;
}
