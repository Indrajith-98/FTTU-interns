#ifndef RANDOMHORIZONTALSHIFT_H
#define RANDOMHORIZONTALSHIFT_H

#include <opencv2/opencv.hpp>
#include <cstdlib>  // For rand()

cv::Mat randomHorizontalShift(const cv::Mat& inputImage, int maxShift);

#endif // RANDOMHORIZONTALSHIFT_H
