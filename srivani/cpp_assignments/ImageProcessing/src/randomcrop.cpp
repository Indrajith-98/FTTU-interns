#include "RandomCrop.h"
#include <opencv2/opencv.hpp>  // Make sure to include OpenCV headers for displaying images

cv::Mat randomCrop(const cv::Mat& inputImage, int cropWidth, int cropHeight) {
    int maxX = inputImage.cols - cropWidth;
    int maxY = inputImage.rows - cropHeight;

    // Ensure the crop area fits within the image
    if (maxX < 0 || maxY < 0) {
        throw std::runtime_error("Crop size is larger than the input image dimensions");
    }

    // Generate random starting points for the crop, ensuring they are within the bounds
    int startX = rand() % (maxX + 1);  // Ensure startX is within bounds
    int startY = rand() % (maxY + 1);  // Ensure startY is within bounds

    // Crop the image and return
    cv::Rect cropRegion(startX, startY, cropWidth, cropHeight);
    cv::Mat croppedImage = inputImage(cropRegion);

    return croppedImage;
}
