#include "RandomHorizontalShift.h"
#include <opencv2/opencv.hpp>  // Ensure OpenCV headers are included for image display

cv::Mat randomHorizontalShift(const cv::Mat& inputImage, int maxShift) {
    // Ensure the shift does not exceed image dimensions
    if (maxShift >= inputImage.cols) {
        throw std::runtime_error("Shift value is larger than image width");
    }

    // Generate a random shift value between -maxShift and +maxShift
    int shift = rand() % (2 * maxShift + 1) - maxShift;  // Include zero shift in the range

    cv::Mat shiftedImage;

    // If the shift is positive, shift right; otherwise, shift left
    if (shift > 0) {
        cv::Rect shiftRegion(shift, 0, inputImage.cols - shift, inputImage.rows);
        cv::Mat croppedImage = inputImage(shiftRegion);
        cv::Mat paddingImage(inputImage.rows, shift, inputImage.type(), cv::Scalar(0, 0, 0));
        cv::hconcat(paddingImage, croppedImage, shiftedImage);
    } else {
        cv::Rect shiftRegion(0, 0, inputImage.cols + shift, inputImage.rows);
        cv::Mat croppedImage = inputImage(shiftRegion);
        cv::Mat paddingImage(inputImage.rows, -shift, inputImage.type(), cv::Scalar(0, 0, 0));
        cv::hconcat(croppedImage, paddingImage, shiftedImage);
    }

    return shiftedImage;
}
