#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <resize.h>

using namespace cv;
using namespace std;

Mat resizeImage(const Mat& img, int newWidth, int newHeight) {
    Mat resized(newHeight, newWidth, img.type());

    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            int origX = static_cast<int>(x * (img.cols / static_cast<float>(newWidth)));
            int origY = static_cast<int>(y * (img.rows / static_cast<float>(newHeight)));
            resized.at<Vec3b>(y, x) = img.at<Vec3b>(origY, origX);
        }
    }
    return resized;
}