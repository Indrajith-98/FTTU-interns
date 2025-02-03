#ifndef IMAGE_READER_H
#define IMAGE_READER_H

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

class ImageReader {
public:
    ImageReader(const std::string& filePath);

    std::vector<std::vector<std::vector<double>>> readImage();

private:
    std::string filePath;
};

#endif // IMAGE_READER_H

