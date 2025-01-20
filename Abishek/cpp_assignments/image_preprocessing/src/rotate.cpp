#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <random>
#include <rotate.h>

using namespace cv;
using namespace std;

Mat randomRotate(const Mat& img, double maxAngle) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(-maxAngle, maxAngle);
    double angle = dist(gen);

    int centerX = img.cols / 2;
    int centerY = img.rows / 2;

    double radians = angle * CV_PI / 180.0;
    Mat rotated(img.size(), img.type(), Scalar(0, 0, 0));

    for (int y = 0; y < img.rows; ++y) {
        for (int x = 0; x < img.cols; ++x) {
            int newX = static_cast<int>(cos(radians) * (x - centerX) - sin(radians) * (y - centerY) + centerX);
            int newY = static_cast<int>(sin(radians) * (x - centerX) + cos(radians) * (y - centerY) + centerY);

            if (newX >= 0 && newX < img.cols && newY >= 0 && newY < img.rows) {
                rotated.at<Vec3b>(y, x) = img.at<Vec3b>(newY, newX);
            }
        }
    }
    return rotated;
}