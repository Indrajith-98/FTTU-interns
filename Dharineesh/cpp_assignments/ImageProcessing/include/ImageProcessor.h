#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

class ImageProcessor {
public:
    ImageProcessor(const std::string& imagePath);
    virtual ~ImageProcessor() = default;
    virtual void process() = 0;  // Pure virtual function to be implemented by derived classes
    void save(const std::string& outputPath);

protected:
    std::vector<unsigned char> image;
    int width = 0, height = 0, channels = 3;
    void loadImage(const std::string& imagePath);
};

#endif
