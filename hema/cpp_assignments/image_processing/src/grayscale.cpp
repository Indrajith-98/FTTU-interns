#include "grayscale.h"
#include <iostream>

void toGrayscale(ImageProcessor &processor) {
    if (processor.channels == 1) {
        std::cout << "Image is already grayscale." << std::endl;
        return;
    }
    for (int i = 0; i < processor.height; i++) {
        for (int j = 0; j < processor.width; j++) {
            unsigned char gray = static_cast<unsigned char>(
                0.299 * processor.image_data[i][j][2] +
                0.587 * processor.image_data[i][j][1] +
                0.114 * processor.image_data[i][j][0]);
            processor.image_data[i][j] = {gray, gray, gray};
        }
    }
    processor.channels = 1;
    std::cout << "Converted to grayscale." << std::endl;
}
