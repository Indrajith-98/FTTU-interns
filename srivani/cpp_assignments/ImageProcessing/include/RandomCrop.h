#ifndef RANDOMCROP_H
#define RANDOMCROP_H

#include <opencv2/opencv.hpp>
#include <cstdlib>  // For rand()

cv::Mat randomCrop(const cv::Mat& inputImage, int cropWidth, int cropHeight);

#endif // RANDOMCROP_H
