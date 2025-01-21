#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <vector>
#include <string>

class ImageProcessor {
public:

    static std::vector<std::vector<std::vector<uint8_t>>> grayscale(const std::vector<std::vector<std::vector<uint8_t>>>& image);
    static std::vector<std::vector<std::vector<uint8_t>>> invert(const std::vector<std::vector<std::vector<uint8_t>>>& image);
    static std::vector<std::vector<std::vector<uint8_t>>> adjustBrightness(const std::vector<std::vector<std::vector<uint8_t>>>& image, int delta);
    static std::vector<std::vector<std::vector<uint8_t>>> normalize(const std::vector<std::vector<std::vector<uint8_t>>>& image);
    static std::vector<std::vector<std::vector<uint8_t>>> gaussianBlur(const std::vector<std::vector<std::vector<uint8_t>>>& image);
};

#endif
