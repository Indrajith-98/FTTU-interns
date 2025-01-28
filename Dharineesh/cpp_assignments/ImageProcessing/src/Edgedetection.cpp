#include "EdgeDetection.h"
#include <cmath>

EdgeDetection::EdgeDetection(const std::string& imagePath) 
    : ImageProcessor(imagePath) {}

void EdgeDetection::process() {
    std::vector<unsigned char> edgeImage(width * height * channels, 0);

    int kernelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int kernelY[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            int gx = 0, gy = 0;
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    int pixel = image[((y + ky) * width + (x + kx)) * channels];
                    gx += kernelX[ky + 1][kx + 1] * pixel;
                    gy += kernelY[ky + 1][kx + 1] * pixel;
                }
            }

            int magnitude = static_cast<int>(std::sqrt(gx * gx + gy * gy));
            magnitude = std::min(255, magnitude);
            edgeImage[(y * width + x) * channels] = magnitude;
            edgeImage[(y * width + x) * channels + 1] = magnitude;
            edgeImage[(y * width + x) * channels + 2] = magnitude;
        }
    }

    image = std::move(edgeImage);
}
