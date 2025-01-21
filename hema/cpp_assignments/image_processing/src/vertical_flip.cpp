#include "vertical_flip.h"
#include <iostream>

void flipVertical(ImageProcessor &processor) {
    for (int i = 0; i < processor.height / 2; i++) {
        std::swap(processor.image_data[i], processor.image_data[processor.height - 1 - i]);
    }
    std::cout << "Image flipped vertically." << std::endl;
}
