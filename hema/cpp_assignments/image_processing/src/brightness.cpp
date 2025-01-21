#include "brightness.h"
#include <iostream>
#include <algorithm>

void adjustBrightness(ImageProcessor &processor, int value) {
    for (int i = 0; i < processor.height; i++) {
        for (int j = 0; j < processor.width; j++) {
            for (int k = 0; k < processor.channels; k++) {
                int adjusted = processor.image_data[i][j][k] + value;
                processor.image_data[i][j][k] = static_cast<unsigned char>(std::min(255, std::max(0, adjusted)));
            }
        }
    }
    std::cout << "Brightness adjusted by " << value << "." << std::endl;
}
