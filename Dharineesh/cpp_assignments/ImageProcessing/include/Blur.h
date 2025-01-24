#ifndef BLUR_H
#define BLUR_H

#include "ImageProcessor.h"

class Blur : public ImageProcessor {
public:
    Blur(const std::string& imagePath, int kernelSize);
    void process() override;

private:
    int kernelSize;
};

#endif
