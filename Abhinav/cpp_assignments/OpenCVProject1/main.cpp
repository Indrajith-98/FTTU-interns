#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class ImageProcessor {
public:
    // Convert the image to grayscale
    //convert
    Mat convertToGrayscale(const Mat& image) {
        Mat grayImage = image.clone();
        for (int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                Vec3b pixel = image.at<Vec3b>(i, j);
                uchar gray = static_cast<uchar>(0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0]);
                grayImage.at<Vec3b>(i, j) = Vec3b(gray, gray, gray);
            }
        }
        return grayImage;
    }

    // Invert the image colors
    Mat invertImage(const Mat& image) {
        Mat invertedImage = image.clone();
        for (int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                Vec3b pixel = image.at<Vec3b>(i, j);
                invertedImage.at<Vec3b>(i, j) = Vec3b(255 - pixel[0], 255 - pixel[1], 255 - pixel[2]);
            }
        }
        return invertedImage;
    }

    // Adjust the brightness of the image
    Mat adjustBrightness(const Mat& image, int brightness) {
        Mat brightImage = image.clone();
        for (int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                Vec3b pixel = image.at<Vec3b>(i, j);
                brightImage.at<Vec3b>(i, j) = Vec3b(
                    saturate_cast<uchar>(pixel[0] + brightness),
                    saturate_cast<uchar>(pixel[1] + brightness),
                    saturate_cast<uchar>(pixel[2] + brightness)
                );
            }
        }
        return brightImage;
    }

    // Apply edge detection using a simple kernel
    Mat detectEdges(const Mat& image) {
        Mat grayImage = convertToGrayscale(image);
        Mat edgeImage = grayImage.clone();
        int kernel[3][3] = { {-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1} };
        for (int i = 1; i < grayImage.rows - 1; i++) {
            for (int j = 1; j < grayImage.cols - 1; j++) {
                int sum = 0;
                for (int ki = -1; ki <= 1; ki++) {
                    for (int kj = -1; kj <= 1; kj++) {
                        sum += kernel[ki + 1][kj + 1] * grayImage.at<Vec3b>(i + ki, j + kj)[0];
                    }
                }
                edgeImage.at<Vec3b>(i, j) = Vec3b(
                    saturate_cast<uchar>(sum),
                    saturate_cast<uchar>(sum),
                    saturate_cast<uchar>(sum)
                );
            }
        }
        return edgeImage;
    }

    // Flip the image horizontally
    Mat flipImage(const Mat& image) {
        Mat flippedImage = image.clone();
        for (int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                flippedImage.at<Vec3b>(i, image.cols - j - 1) = image.at<Vec3b>(i, j);
            }
        }
        return flippedImage;
    }
};

int main() {
    // Load the input image
    Mat image = imread("C:/Users/HP/OneDrive/Pictures/Cars/laferrari.jpg");
    if (image.empty()) {
        cout << "Error: Unable to load the image!" << endl;
        return -1;
    }

    ImageProcessor processor;

    // Apply the operations
    Mat grayImage = processor.convertToGrayscale(image);
    Mat invertedImage = processor.invertImage(image);
    Mat brightImage = processor.adjustBrightness(image, 50); // Increase brightness by 50
    Mat edgeImage = processor.detectEdges(image);
    Mat flippedImage = processor.flipImage(image);

    // Save the results
    imwrite("gray_image.jpg", grayImage);
    imwrite("inverted_image.jpg", invertedImage);
    imwrite("bright_image.jpg", brightImage);
    imwrite("edge_image.jpg", edgeImage);
    imwrite("flipped_image.jpg", flippedImage);

    cout << "Image processing operations completed. Results saved." << endl;
    return 0;
}
