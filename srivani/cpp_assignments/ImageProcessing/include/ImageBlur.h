#ifndef IMAGEBLUR_H
#define IMAGEBLUR_H

#include <opencv2/opencv.hpp>
#include <string>

cv::Mat applyGaussianBlur(const cv::Mat& inputImage, int kernelSize);

#endif // IMAGEBLUR_H
