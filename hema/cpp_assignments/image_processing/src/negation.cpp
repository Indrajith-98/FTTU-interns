#include "negation.h"
#include <iostream>

void negateImage(ImageProcessor &processor) {
    for (int i = 0; i < processor.height; i++) {
        for (int j = 0; j < processor.width; j++) {
            for (int k = 0; k < processor.channels; k++) {
                processor.image_data[i][j][k] = 255 - processor.image_data[i][j][k];
            }
        }
    }
    std::cout << "Image negated." << std::endl;
}
