#include "ImageProcessing.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <vector>

// Utility function to convert OpenCV Mat to 3D vector
std::vector<std::vector<std::vector<uint8_t>>> matToVector(const cv::Mat& mat) {
    std::vector<std::vector<std::vector<uint8_t>>> vec(mat.rows, std::vector<std::vector<uint8_t>>(mat.cols, std::vector<uint8_t>(3)));

    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            cv::Vec3b pixel = mat.at<cv::Vec3b>(i, j);
            vec[i][j][0] = pixel[0];
            vec[i][j][1] = pixel[1];
            vec[i][j][2] = pixel[2];
        }
    }
    return vec;
}

// Utility function to convert 3D vector to OpenCV Mat
cv::Mat vectorToMat(const std::vector<std::vector<std::vector<uint8_t>>>& vec) {
    int rows = vec.size();
    int cols = vec[0].size();
    cv::Mat mat(rows, cols, CV_8UC3);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat.at<cv::Vec3b>(i, j) = cv::Vec3b(vec[i][j][0], vec[i][j][1], vec[i][j][2]);
        }
    }
    return mat;
}

int main() {
    // Input image path
    std::string inputPath = "F:/MCW/Assignment 2/test images/cat.jpeg";

    // Output directory
    std::string outputDir = "F:/MCW/training assignments/CPP_assignments/Image_Preprocessing/output_images";

    // Create the output directory if it doesn't exist
    if (!std::filesystem::exists(outputDir)) {
        std::filesystem::create_directories(outputDir);
    }

    // Read the image using OpenCV
    cv::Mat image = cv::imread(inputPath);
    if (image.empty()) {
        std::cerr << "Error: Could not load the image at " << inputPath << "\n";
        return -1;
    }

    // Convert image to 3D vector
    auto imageVector = matToVector(image);

    // Apply custom grayscale
    auto grayVector = ImageProcessor::grayscale(imageVector);
    cv::Mat grayImage = vectorToMat(grayVector);
    cv::imwrite(outputDir + "/gray_image.jpg", grayImage);

    // Apply custom inversion
    auto invertedVector = ImageProcessor::invert(imageVector);
    cv::Mat invertedImage = vectorToMat(invertedVector);
    cv::imwrite(outputDir + "/inverted_image.jpg", invertedImage);

    // Apply custom brightness adjustment
    auto brightVector = ImageProcessor::adjustBrightness(imageVector, 50);
    cv::Mat brightImage = vectorToMat(brightVector);
    cv::imwrite(outputDir + "/bright_image.jpg", brightImage);

    // Apply custom normalization
    auto normalizedVector = ImageProcessor::normalize(imageVector);
    cv::Mat normalizedImage = vectorToMat(normalizedVector);
    cv::imwrite(outputDir + "/normalized_image.jpg", normalizedImage);

    // Apply custom Gaussian blur
    auto blurredVector = ImageProcessor::gaussianBlur(imageVector);
    cv::Mat blurredImage = vectorToMat(blurredVector);
    cv::imwrite(outputDir + "/blurred_image.jpg", blurredImage);

    std::cout << "Processing complete. Check the output images in: " << outputDir << "\n";
    return 0;
}
