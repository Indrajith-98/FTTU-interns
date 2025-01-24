#include "ImageProcessor.h"
#include <iostream>

int main() {
    // Create ImageProcessor instance
    ImageProcessor processor;
    
    // Make sure to use the correct path to the image
    std::vector<std::vector<std::vector<unsigned char>>> image = processor.readImage("E:/image processing/goat.jpg");

    // Get processed images
    std::vector<std::vector<std::vector<unsigned char>>> inverted = processor.invertColors(image);
    processor.saveImage("E:/image processing/output_images/inver_color_output.jpg", inverted);

    std::vector<std::vector<std::vector<unsigned char>>> grayscale = processor.toGrayscale(image);
    processor.saveImage("E:/image processing/output_images/gray_scale_output.jpg", grayscale);

    std::vector<std::vector<std::vector<unsigned char>>> blurred = processor.blur(image);
    processor.saveImage("E:/image processing/output_images/blur_output.jpg", blurred);

    std::vector<std::vector<std::vector<unsigned char>>> bright = processor.adjustBrightness(image, 50);  // Brightness increase by 50
    processor.saveImage("E:/image processing/output_images/adjustBrightness_output.jpg", bright);

    std::vector<std::vector<std::vector<unsigned char>>> contrast = processor.adjustContrast(image, 1.5);  // Increase contrast by 1.5
    processor.saveImage("E:/image processing/output_images/adjustContrast_output.jpg", contrast);


    return 0;
   
}
