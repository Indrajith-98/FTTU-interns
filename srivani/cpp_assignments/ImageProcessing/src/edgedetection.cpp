#include "EdgeDetection.h"
#include <opencv2/opencv.hpp>

cv::Mat applyEdgeDetection(const cv::Mat& inputImage, double lowThreshold, double highThreshold) {
    cv::Mat edges;

    // Convert the image to grayscale if it's not already
    if (inputImage.channels() == 3) {
        cv::cvtColor(inputImage, edges, cv::COLOR_BGR2GRAY);
    } else {
        edges = inputImage.clone();
    }

    // Apply Gaussian blur to reduce noise and improve edge detection
    cv::GaussianBlur(edges, edges, cv::Size(5, 5), 1.5);

    // Use the Canny edge detector
    cv::Canny(edges, edges, lowThreshold, highThreshold);

    return edges;
}
