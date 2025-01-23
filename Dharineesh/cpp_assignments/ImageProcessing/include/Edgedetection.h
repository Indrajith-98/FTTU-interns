#ifndef EDGE_DETECTION_H
#define EDGE_DETECTION_H

#include "ImageProcessor.h"

class EdgeDetection : public ImageProcessor {
public:
    EdgeDetection(const std::string& imagePath);
    void process() override;
};

#endif
