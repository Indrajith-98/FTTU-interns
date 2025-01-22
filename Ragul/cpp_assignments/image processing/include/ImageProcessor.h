#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <string>
#include <vector>

class ImageProcessor {
public:
    // Reads image from the specified path and returns it as a 3D vector
    std::vector<std::vector<std::vector<unsigned char>>> readImage(const std::string& imagePath);    

    std::vector<std::vector<std::vector<unsigned char>>> invertColors(const std::vector<std::vector<std::vector<unsigned char>>>& img);

    std::vector<std::vector<std::vector<unsigned char>>> toGrayscale(const std::vector<std::vector<std::vector<unsigned char>>>& img);

    std::vector<std::vector<std::vector<unsigned char>>> blur(const std::vector<std::vector<std::vector<unsigned char>>>& img);

    std::vector<std::vector<std::vector<unsigned char>>> adjustBrightness( const std::vector<std::vector<std::vector<unsigned char>>>& img, int brightness); 

    std::vector<std::vector<std::vector<unsigned char>>> adjustContrast(const std::vector<std::vector<std::vector<unsigned char>>>& img, double contrast);
    
    // Functions to save 
    void saveImage(const std::string& outputPath, const std::vector<std::vector<std::vector<unsigned char>>>& img);

  
};

#endif // IMAGEPROCESSOR_H
