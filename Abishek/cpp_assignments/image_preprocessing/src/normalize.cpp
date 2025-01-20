#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <normalize.h>

using namespace cv;
using namespace std;

Mat normalizeImage(const Mat& img) {
    Mat normalized = img.clone();

    for (int y = 0; y < img.rows; ++y) {
        for (int x = 0; x < img.cols; ++x) {
            Vec3b pixel = img.at<Vec3b>(y, x);
            normalized.at<Vec3b>(y, x)[0] = static_cast<uchar>(pixel[0] / 255.0 * 255);
            normalized.at<Vec3b>(y, x)[1] = static_cast<uchar>(pixel[1] / 255.0 * 255);
            normalized.at<Vec3b>(y, x)[2] = static_cast<uchar>(pixel[2] / 255.0 * 255);
        }
    }
    return normalized;
}