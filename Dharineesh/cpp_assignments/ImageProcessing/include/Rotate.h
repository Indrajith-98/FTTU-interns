#ifndef ROTATE_H
#define ROTATE_H

#include "ImageProcessor.h"

class Rotate : public ImageProcessor {
public:
    Rotate(const std::string& imagePath);
    void process() override;
};

#endif
