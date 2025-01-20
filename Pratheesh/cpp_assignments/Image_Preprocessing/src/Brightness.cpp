#include "ImageProcessing.h"
#include <algorithm>

std::vector<std::vector<std::vector<uint8_t>>> ImageProcessor::adjustBrightness(const std::vector<std::vector<std::vector<uint8_t>>>& image, int delta) {
    auto result = image;
    for (auto& row : result) {
        for (auto& pixel : row) {
            for (int i = 0; i < 3; ++i) {
                pixel[i] = std::clamp(pixel[i] + delta, 0, 255);
            }
        }
    }
    return result;
}
