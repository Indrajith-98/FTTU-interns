#include "ImageProcessing.h"
#include <algorithm>
#include <cmath>

std::vector<std::vector<std::vector<uint8_t>>> ImageProcessor::normalize(const std::vector<std::vector<std::vector<uint8_t>>>& image) {
    auto result = image;

    uint8_t minVal = 255, maxVal = 0;

    // Find min and max pixel values across all channels
    for (const auto& row : image) {
        for (const auto& pixel : row) {
            for (int i = 0; i < 3; ++i) {
                minVal = std::min(minVal, pixel[i]);
                maxVal = std::max(maxVal, pixel[i]);
            }
        }
    }

    // Perform normalization
    for (auto& row : result) {
        for (auto& pixel : row) {
            for (int i = 0; i < 3; ++i) {
                pixel[i] = static_cast<uint8_t>((pixel[i] - minVal) * 255.0 / (maxVal - minVal));
            }
        }
    }

    return result;
}
