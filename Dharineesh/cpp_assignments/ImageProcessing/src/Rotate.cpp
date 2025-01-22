#include "Rotate.h"

Rotate::Rotate(const std::string& imagePath) 
    : ImageProcessor(imagePath) {}

void Rotate::process() {
    std::vector<unsigned char> rotatedImage(width * height * channels);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int srcOffset = (y * width + x) * channels;
            int dstOffset = ((x + 1) * height - y - 1) * channels;

            for (int c = 0; c < channels; ++c) {
                rotatedImage[dstOffset + c] = image[srcOffset + c];
            }
        }
    }

    image = std::move(rotatedImage);
    std::swap(width, height);
}
