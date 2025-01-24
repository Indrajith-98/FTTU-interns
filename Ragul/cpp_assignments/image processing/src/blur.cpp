#include "../include/ImageProcessor.h"

#include "../include/ImageProcessor.h"

std::vector<std::vector<std::vector<unsigned char>>> ImageProcessor::blur(const std::vector<std::vector<std::vector<unsigned char>>>& img) {
    int rows = img.size();
    int cols = img[0].size();
    std::vector<std::vector<std::vector<unsigned char>>> newImage(rows, std::vector<std::vector<unsigned char>>(cols, std::vector<unsigned char>(3, 0)));

    // Define the kernel size (e.g., 5x5)
    int kernelSize = 8;
    int halfKernel = kernelSize / 2;

    // Iterate over each pixel in the image
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            unsigned int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            // Sum the values of the neighboring pixels within the kernel
            for (int dy = -halfKernel; dy <= halfKernel; ++dy) {
                for (int dx = -halfKernel; dx <= halfKernel; ++dx) {
                    int ni = i + dy;
                    int nj = j + dx;
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                        sumB += img[ni][nj][0];
                        sumG += img[ni][nj][1];
                        sumR += img[ni][nj][2];
                        count++;
                    }
                }
            }

            // Compute the average for the surrounding pixels
            newImage[i][j][0] = static_cast<unsigned char>(sumB / count);
            newImage[i][j][1] = static_cast<unsigned char>(sumG / count);
            newImage[i][j][2] = static_cast<unsigned char>(sumR / count);
        }
    }

    return newImage;  // Return the new blurred image
}
