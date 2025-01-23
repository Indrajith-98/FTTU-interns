#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "ImageProcessor.h"

class Grayscale : public ImageProcessor {
public:
    Grayscale(const std::string& imagePath);
    void process() override;
};

#endif
