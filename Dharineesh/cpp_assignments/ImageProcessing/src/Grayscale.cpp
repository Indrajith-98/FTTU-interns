#include "Grayscale.h"

Grayscale::Grayscale(const std::string& imagePath) 
    : ImageProcessor(imagePath) {}

void Grayscale::process() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int offset = (y * width + x) * channels;
            unsigned char r = image[offset];
            unsigned char g = image[offset + 1];
            unsigned char b = image[offset + 2];

            unsigned char gray = static_cast<unsigned char>(0.2989 * r + 0.5870 * g + 0.1140 * b);
            image[offset] = image[offset + 1] = image[offset + 2] = gray;
        }
    }
}
