#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <vector>
#include <string>

class ImageProcessor {
private:
    std::vector<std::vector<std::vector<unsigned char>>> image_data;
    int width, height, channels;

public:
    bool loadImage(const std::string &file_path);
    void saveImage(const std::string &file_path);

    // Friend functions for modular functionality
    friend void toGrayscale(ImageProcessor &processor);
    friend void negateImage(ImageProcessor &processor);
    friend void adjustBrightness(ImageProcessor &processor, int value);
    friend void flipHorizontal(ImageProcessor &processor);
    friend void flipVertical(ImageProcessor &processor);
};

#endif
