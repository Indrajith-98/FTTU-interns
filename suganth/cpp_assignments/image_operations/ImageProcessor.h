#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

class ImageProcessor {
public:
    int rows, cols, channels;
    std::vector<std::vector<std::vector<unsigned char>>> image_data;

    ImageProcessor(const std::string& imagePath);
    
    void toGrayscale();
    void resize(int new_width, int new_height);
    void flipHorizontal();
    void flipVertical();
    void rotate90();
    void saveImage(const std::vector<std::vector<std::vector<unsigned char>>>& img_data, const std::string& outputPath, int final_rows, int final_cols);
};

#endif // IMAGEPROCESSOR_H
