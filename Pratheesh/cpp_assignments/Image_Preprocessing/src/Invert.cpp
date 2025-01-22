#include "ImageProcessing.h"

std::vector<std::vector<std::vector<uint8_t>>> ImageProcessor::invert(const std::vector<std::vector<std::vector<uint8_t>>>& image) {
    auto result = image;
    for (auto& row : result) {
        for (auto& pixel : row) {
            pixel[0] = 255 - pixel[0]; // Blue
            pixel[1] = 255 - pixel[1]; // Green
            pixel[2] = 255 - pixel[2]; // Red
        }
    }
    return result;
}
