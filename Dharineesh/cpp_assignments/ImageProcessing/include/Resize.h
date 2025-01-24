#ifndef RESIZE_H
#define RESIZE_H

#include "ImageProcessor.h"

class Resize : public ImageProcessor {
public:
    Resize(const std::string& imagePath, int newWidth, int newHeight);
    void process() override;

private:
    int newWidth, newHeight;
};

#endif
