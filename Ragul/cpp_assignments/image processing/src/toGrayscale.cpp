#include "ImageProcessor.h"

std::vector<std::vector<std::vector<unsigned char>>> ImageProcessor::toGrayscale(const std::vector<std::vector<std::vector<unsigned char>>>& img) {
    std::vector<std::vector<std::vector<unsigned char>>> newImage = img;
    
    for (size_t i = 0; i < newImage.size(); i++) {
        for (size_t j = 0; j < newImage[i].size(); j++) {
            unsigned char gray = static_cast<unsigned char>(0.299 * newImage[i][j][0] + 0.587 * newImage[i][j][1] + 0.114 * newImage[i][j][2]);
            newImage[i][j][0] = gray;
            newImage[i][j][1] = gray;
            newImage[i][j][2] = gray;
        }
    }
    
    return newImage;
}