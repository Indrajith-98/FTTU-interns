#ifndef EDGEDETECTION_H
#define EDGEDETECTION_H

#include <opencv2/opencv.hpp>

cv::Mat applyEdgeDetection(const cv::Mat& inputImage, double lowThreshold, double highThreshold);

#endif // EDGEDETECTION_H
