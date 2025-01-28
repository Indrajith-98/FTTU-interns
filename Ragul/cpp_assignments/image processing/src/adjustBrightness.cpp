#include "ImageProcessor.h"
#include<vector>
#include <algorithm> 

std::vector<std::vector<std::vector<unsigned char>>> ImageProcessor::adjustBrightness(
    const std::vector<std::vector<std::vector<unsigned char>>>& image, int brightness) {
    
    int rows = image.size();
    int cols = image[0].size();
    std::vector<std::vector<std::vector<unsigned char>>> result(rows, std::vector<std::vector<unsigned char>>(cols, std::vector<unsigned char>(3)));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int c = 0; c < 3; ++c) {
                result[i][j][c] = std::min(255, std::max(0, image[i][j][c] + brightness)); // Apply brightness
            }
        }
    }

    return result;
}
