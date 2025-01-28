#include "ImageBlur.h"
#include <opencv2/opencv.hpp>

cv::Mat applyGaussianBlur(const cv::Mat& inputImage, int kernelSize) {
    if (kernelSize % 2 == 0) {
        kernelSize++;  // Ensure kernel size is odd
    }

    cv::Mat blurredImage;
    cv::GaussianBlur(inputImage, blurredImage, cv::Size(kernelSize, kernelSize), 0);
    return blurredImage;
}
