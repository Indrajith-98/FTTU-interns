#ifndef RESIZE_IMAGE_H
#define RESIZE_IMAGE_H

#include <opencv4/opencv2/opencv.hpp>
#include <iostream>

cv::Mat resizeImage(const cv::Mat& img, int newWidth, int newHeight);

#endif // RESIZE_IMAGE_H