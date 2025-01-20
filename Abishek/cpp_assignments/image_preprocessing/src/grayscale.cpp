#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <grayscale.h>

using namespace cv;
using namespace std;

Mat convertToGrayscale(const Mat& img) {
    Mat gray(img.rows, img.cols, CV_8UC1);

    for (int y = 0; y < img.rows; ++y) {
        for (int x = 0; x < img.cols; ++x) {
            Vec3b pixel = img.at<Vec3b>(y, x);
            gray.at<uchar>(y, x) = static_cast<uchar>(0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0]);
        }
    }
    return gray;
}