#include "Blur.h"

Blur::Blur(const std::string& imagePath, int kernelSize) 
    : ImageProcessor(imagePath), kernelSize(kernelSize) {}

void Blur::process() {
    std::vector<unsigned char> blurredImage(width * height * channels, 0);
    int halfKernel = kernelSize / 2;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int sum[3] = {0, 0, 0};
            int count = 0;

            for (int ky = -halfKernel; ky <= halfKernel; ++ky) {
                for (int kx = -halfKernel; kx <= halfKernel; ++kx) {
                    int nx = x + kx;
                    int ny = y + ky;

                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        int offset = (ny * width + nx) * channels;
                        for (int c = 0; c < channels; ++c) {
                            sum[c] += image[offset + c];
                        }
                        ++count;
                    }
                }
            }

            int dstOffset = (y * width + x) * channels;
            for (int c = 0; c < channels; ++c) {
                blurredImage[dstOffset + c] = sum[c] / count;
            }
        }
    }

    image = std::move(blurredImage);
}
