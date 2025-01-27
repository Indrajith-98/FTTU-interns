#include <opencv2/opencv.hpp>
#include <iostream>

cv::Mat convert_into_grayscale_image(const cv::Mat& inputImage) {
    cv::Mat grayscaleImage(inputImage.rows, inputImage.cols, CV_8UC1);

    for (int y = 0; y < inputImage.rows; ++y) {
        for (int x = 0; x < inputImage.cols; ++x) {
            cv::Vec3b rgbPixel = inputImage.at<cv::Vec3b>(y, x);
            uchar R = rgbPixel[2];
            uchar G = rgbPixel[1];
            uchar B = rgbPixel[0];
            uchar grayValue = static_cast<uchar>(0.2989 * R + 0.5870 * G + 0.1140 * B);
            grayscaleImage.at<uchar>(y, x) = grayValue;
        }
    }

    return grayscaleImage;
}


cv::Mat rotate_image_by_angle(const cv::Mat& inputImage, double angle) {

    int imgHeight = inputImage.rows;
    int imgWidth = inputImage.cols;

    int centerX = imgWidth / 2;
    int centerY = imgHeight / 2;

    double radians = angle * CV_PI / 180.0;

    cv::Mat rotatedImage = cv::Mat::zeros(imgHeight, imgWidth, inputImage.type());

    for (int y = 0; y < imgHeight; y++) {
        for (int x = 0; x < imgWidth; x++) {
            int relX = x - centerX;
            int relY = y - centerY;
            int newX = std::round(centerX + (relX * std::cos(radians) - relY * std::sin(radians)));
            int newY = std::round(centerY + (relX * std::sin(radians) + relY * std::cos(radians)));
            if (newX >= 0 && newX < imgWidth && newY >= 0 && newY < imgHeight) {
                rotatedImage.at<cv::Vec3b>(y, x) = inputImage.at<cv::Vec3b>(newY, newX);
            }
        }
    }

    return rotatedImage;
}

cv::Mat flipVertically(const cv::Mat& image) {
    int imgHeight = image.rows;
    int imgWidth = image.cols;

    cv::Mat flippedImage = image.clone();
    for (int y = 0; y < imgHeight / 2; y++) {
        for (int x = 0; x < imgWidth; x++) {
            cv::Vec3b temp = flippedImage.at<cv::Vec3b>(y, x);
            flippedImage.at<cv::Vec3b>(y, x) = flippedImage.at<cv::Vec3b>(imgHeight - y - 1, x);
            flippedImage.at<cv::Vec3b>(imgHeight - y - 1, x) = temp;
        }
    }

    return flippedImage;
}

cv::Mat manualZoomIn(const cv::Mat& image, float zoomFactor) {
    int originalHeight = image.rows;
    int originalWidth = image.cols;

    int newHeight = static_cast<int>(originalHeight / zoomFactor);
    int newWidth = static_cast<int>(originalWidth / zoomFactor);

    cv::Mat zoomedImage = cv::Mat::zeros(newHeight, newWidth, image.type());

    int centerX = originalWidth / 2;
    int centerY = originalHeight / 2;

    int offsetX = (originalWidth - newWidth) / 2;
    int offsetY = (originalHeight - newHeight) / 2;

    for (int y = 0; y < newHeight; y++) {
        for (int x = 0; x < newWidth; x++) {
            int originalY = y + offsetY;
            int originalX = x + offsetX;

            originalY = std::min(std::max(originalY, 0), originalHeight - 1);
            originalX = std::min(std::max(originalX, 0), originalWidth - 1);

            zoomedImage.at<cv::Vec3b>(y, x) = image.at<cv::Vec3b>(originalY, originalX);
        }
    }

    return zoomedImage;

}

cv::Mat sobelEdgeDetection(const cv::Mat& input_image) {
    if (input_image.channels() > 1) {
        std::cerr << "Input image must be grayscale." << std::endl;
        return cv::Mat();
    }

    int rows = input_image.rows;
    int cols = input_image.cols;

    int Mx[3][3] = { {-1, 0, 1},
                     {-2, 0, 2},
                     {-1, 0, 1} };
                     
    int My[3][3] = { {-1, -2, -1},
                     { 0,  0,  0},
                     { 1,  2,  1} };

    cv::Mat filtered_image = cv::Mat::zeros(rows, cols, CV_32F);  
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            float Gx = 0, Gy = 0;
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    Gx += input_image.at<uchar>(i + ky, j + kx) * Mx[ky + 1][kx + 1];
                    Gy += input_image.at<uchar>(i + ky, j + kx) * My[ky + 1][kx + 1];
                }
            }

            filtered_image.at<float>(i, j) = std::sqrt(Gx * Gx + Gy * Gy);
        }
    }

    cv::Mat result;
    filtered_image.convertTo(result, CV_8U); 
    return result;
}


int main() {
    cv::Mat image = cv::imread("D:/ImagePreprocessing/img2.jpg", cv::IMREAD_COLOR);

    if (image.empty()) {
        std::cerr << "Could not open or find the image!" << std::endl;
        return -1;
    }

    cv::Mat grayscaleImage = convert_into_grayscale_image(image);

    double rotationAngle;
    std::cout << "Enter the angle (in degrees) to rotate the image: ";
    std::cin >> rotationAngle;
    cv::Mat rotatedImage = rotate_image_by_angle(image, rotationAngle);

    cv::Mat flippedImage = flipVertically(image);
    
    float zoomFactor = 2.0f;
    cv::Mat zoomedImage = manualZoomIn(image, zoomFactor);

    cv::Mat edgeDetectedImg = sobelEdgeDetection(grayscaleImage);
     
    
    cv::imshow("Original Image", image);
    cv::imshow("Grayscale Image", grayscaleImage);
    cv::imshow("Rotated Image", rotatedImage);
    cv::imshow("Vertically Flipped Image", flippedImage);
    cv::imshow("Zoomed-in Image", zoomedImage);
    cv::imshow("Edge Detected Image", edgeDetectedImg);
    
    
    cv::waitKey(0);

    return 0;
}
