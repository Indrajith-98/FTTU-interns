#ifndef IMAGE_OPERATIONS_H
#define IMAGE_OPERATIONS_H

#include <opencv2/opencv.hpp>

// Function declarations for image adjustments
void adjustShadows(const cv::Mat& inputImage, cv::Mat& outputImage, float factor);
void adjustHighlights(const cv::Mat& inputImage, cv::Mat& outputImage, float factor);
void adjustContrast(const cv::Mat& inputImage, cv::Mat& outputImage, float factor);
void adjustSaturation(const cv::Mat& inputImage, cv::Mat& outputImage, float factor);
void convertBGRtoHSV(const cv::Mat& inputImage, cv::Mat& outputImage);

#endif
