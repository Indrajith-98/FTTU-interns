#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <random>
#include <cropping.h>

using namespace cv;
using namespace std;

Mat randomCrop(const Mat& img, int cropWidth, int cropHeight) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> xDist(0, img.cols - cropWidth);
    uniform_int_distribution<> yDist(0, img.rows - cropHeight);

    int x = xDist(gen);
    int y = yDist(gen);

    Mat cropped(cropHeight, cropWidth, img.type());

    for (int i = 0; i < cropHeight; ++i) {
        for (int j = 0; j < cropWidth; ++j) {
            cropped.at<Vec3b>(i, j) = img.at<Vec3b>(y + i, x + j);
        }
    }
    return cropped;
}