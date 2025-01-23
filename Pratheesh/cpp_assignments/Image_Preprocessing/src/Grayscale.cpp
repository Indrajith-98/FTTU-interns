#include "ImageProcessing.h"
#include <cmath>

std::vector<std::vector<std::vector<uint8_t>>> ImageProcessor::grayscale(const std::vector<std::vector<std::vector<uint8_t>>>& image) {
    auto result = image;
    for (auto& row : result) {
        for (auto& pixel : row) {
            uint8_t gray = static_cast<uint8_t>(0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0]);
            pixel[0] = pixel[1] = pixel[2] = gray;
        }
    }
    return result;
}
