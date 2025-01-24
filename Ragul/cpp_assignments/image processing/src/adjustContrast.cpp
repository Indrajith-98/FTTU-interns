#include "ImageProcessor.h"
#include <algorithm>
#include <vector>



std::vector<std::vector<std::vector<unsigned char>>> ImageProcessor::adjustContrast(const std::vector<std::vector<std::vector<unsigned char>>>& img, double contrast) {
    std::vector<std::vector<std::vector<unsigned char>>> newImage = img;

    for (size_t i = 0; i < newImage.size(); i++) {
        for (size_t j = 0; j < newImage[i].size(); j++) {
            for (int c = 0; c < 3; ++c) {
                int new_value = static_cast<int>((newImage[i][j][c] - 128) * contrast + 128);
                newImage[i][j][c] = std::clamp(new_value, 0, 255);
            }
        }
    }

    return newImage;  // Return new image with adjusted contrast
}