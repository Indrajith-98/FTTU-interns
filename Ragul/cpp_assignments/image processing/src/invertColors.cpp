#include "ImageProcessor.h"

std::vector<std::vector<std::vector<unsigned char>>> ImageProcessor::invertColors(const std::vector<std::vector<std::vector<unsigned char>>>& img) {
    std::vector<std::vector<std::vector<unsigned char>>> newImage = img;
    
    for (size_t i = 0; i < newImage.size(); i++) {
        for (size_t j = 0; j < newImage[i].size(); j++) {
            newImage[i][j][0] = 255 - newImage[i][j][0];  // Invert Blue
            newImage[i][j][1] = 255 - newImage[i][j][1];  // Invert Green
            newImage[i][j][2] = 255 - newImage[i][j][2];  // Invert Red
        }
    }
    
    return newImage;
}