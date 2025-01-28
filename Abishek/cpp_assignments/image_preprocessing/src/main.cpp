#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <random>
#include <cmath>
#include <resize.h>
#include <cropping.h>
#include <grayscale.h>
#include <rotate.h>
#include <normalize.h>

using namespace cv;
using namespace std;

int main() {

    string imagePath = "F:/MultiCoreWare/Assignment 1/test_images/test_image_0.jpeg"; // Replace with your image path
    Mat img = imread(imagePath);

    if (img.empty()) {
        cerr << "Error: Unable to read image!" << endl;
        return -1;
    }

    Mat resized = resizeImage(img, 128, 128);
    Mat normalized = normalizeImage(resized);
    Mat gray = convertToGrayscale(resized);
    Mat rotated = randomRotate(resized, 30.0);
    Mat cropped = randomCrop(resized, 100, 100);

    imwrite("F:/MultiCoreWare/Submissions/FTTU-interns/Abishek/cpp_assignments/image_preprocessing/output/resized.jpg", resized);
    imwrite("F:/MultiCoreWare/Submissions/FTTU-interns/Abishek/cpp_assignments/image_preprocessing/output/normalized.jpg", normalized);
    imwrite("F:/MultiCoreWare/Submissions/FTTU-interns/Abishek/cpp_assignments/image_preprocessing/output/gray.jpg", gray);
    imwrite("F:/MultiCoreWare/Submissions/FTTU-interns/Abishek/cpp_assignments/image_preprocessing/output/rotated.jpg", rotated);
    imwrite("F:/MultiCoreWare/Submissions/FTTU-interns/Abishek/cpp_assignments/image_preprocessing/output/cropped.jpg", cropped);

    cout << "Preprocessing complete. Processed images saved." << endl;

}