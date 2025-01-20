#include "ImageProcessing.h"
#include <algorithm>  
#include <vector>

std::vector<std::vector<std::vector<uint8_t>>> ImageProcessor::gaussianBlur(const std::vector<std::vector<std::vector<uint8_t>>>& image) {
    auto result = image;
    std::vector<std::vector<float>> kernel = {
        {1 / 16.0f, 2 / 16.0f, 1 / 16.0f},
        {2 / 16.0f, 4 / 16.0f, 2 / 16.0f},
        {1 / 16.0f, 2 / 16.0f, 1 / 16.0f}
    };

    int rows = image.size();
    int cols = image[0].size();

    for (int y = 1; y < rows - 1; ++y) {
        for (int x = 1; x < cols - 1; ++x) {
            float new_pixel[3] = {0, 0, 0};

            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int c = 0; c < 3; ++c) {
                        new_pixel[c] += image[y + dy][x + dx][c] * kernel[dy + 1][dx + 1];
                    }
                }
            }

            for (int c = 0; c < 3; ++c) {
                result[y][x][c] = std::clamp(static_cast<int>(new_pixel[c]), 0, 255);
            }
        }
    }

    return result;
}
