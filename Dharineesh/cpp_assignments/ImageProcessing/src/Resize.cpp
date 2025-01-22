#include "Resize.h"

Resize::Resize(const std::string& imagePath, int newWidth, int newHeight) 
    : ImageProcessor(imagePath), newWidth(newWidth), newHeight(newHeight) {}

void Resize::process() {
    std::vector<unsigned char> resizedImage(newWidth * newHeight * channels);
    double xRatio = static_cast<double>(width) / newWidth;
    double yRatio = static_cast<double>(height) / newHeight;

    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            int srcX = static_cast<int>(x * xRatio);
            int srcY = static_cast<int>(y * yRatio);
            int dstOffset = (y * newWidth + x) * channels;
            int srcOffset = (srcY * width + srcX) * channels;

            for (int c = 0; c < channels; ++c) {
                resizedImage[dstOffset + c] = image[srcOffset + c];
            }
        }
    }

    image = std::move(resizedImage);
}
