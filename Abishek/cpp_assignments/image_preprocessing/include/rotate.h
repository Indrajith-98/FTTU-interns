#ifndef RANDOM_ROTATE_H
#define RANDOM_ROTATE_H

#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <random>

cv::Mat randomRotate(const cv::Mat& img, double maxAngle);

#endif // RANDOM_ROTATE_H