#ifndef RANDOM_CROP_H
#define RANDOM_CROP_H

#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <random>

cv::Mat randomCrop(const cv::Mat& img, int cropWidth, int cropHeight);

#endif // RANDOM_CROP_H