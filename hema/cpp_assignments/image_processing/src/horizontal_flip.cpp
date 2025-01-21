#include "horizontal_flip.h"
#include <iostream>

void flipHorizontal(ImageProcessor &processor) {
    for (int i = 0; i < processor.height; i++) {
        for (int j = 0; j < processor.width / 2; j++) {
            std::swap(processor.image_data[i][j], processor.image_data[i][processor.width - 1 - j]);
        }
    }
    std::cout << "Image flipped horizontally." << std::endl;
}
