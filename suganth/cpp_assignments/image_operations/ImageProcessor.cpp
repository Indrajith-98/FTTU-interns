#include "ImageProcessor.h"
#include <iostream>
#include <cmath>

ImageProcessor::ImageProcessor(const std::string& imagePath) {
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Error reading image!" << std::endl;
        exit(1);
    }

    rows = image.rows;
    cols = image.cols;
    channels = image.channels();

    image_data.resize(rows, std::vector<std::vector<unsigned char>>(cols, std::vector<unsigned char>(channels)));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
            for (int c = 0; c < channels; ++c) {
                image_data[i][j][c] = pixel[c];
            }
        }
    }
}

void ImageProcessor::toGrayscale() {
    std::vector<std::vector<std::vector<unsigned char>>> grayscale_image(rows,
        std::vector<std::vector<unsigned char>>(cols, std::vector<unsigned char>(3)));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            unsigned char gray = static_cast<unsigned char>(
                0.299 * image_data[i][j][0] + 0.587 * image_data[i][j][1] + 0.114 * image_data[i][j][2]);
            grayscale_image[i][j][0] = grayscale_image[i][j][1] = grayscale_image[i][j][2] = gray;
        }
    }
    saveImage(grayscale_image, "grayscale_image.jpg", rows, cols);
}

void ImageProcessor::resize(int new_width, int new_height) {
    int original_rows = rows;
    int original_cols = cols;

    std::vector<std::vector<std::vector<unsigned char>>> resized_image(new_height,
        std::vector<std::vector<unsigned char>>(new_width, std::vector<unsigned char>(channels)));

    for (int i = 0; i < new_height; ++i) {
        for (int j = 0; j < new_width; ++j) {
            int orig_x = std::min(static_cast<int>(j * static_cast<double>(original_cols) / new_width), original_cols - 1);
            int orig_y = std::min(static_cast<int>(i * static_cast<double>(original_rows) / new_height), original_rows - 1);
            resized_image[i][j] = image_data[orig_y][orig_x];
        }
    }

    saveImage(resized_image, "resized_image.jpg", new_height, new_width);

    rows = original_rows;
    cols = original_cols;
}

void ImageProcessor::flipHorizontal() {
    std::vector<std::vector<std::vector<unsigned char>>> flipped_image(rows,
        std::vector<std::vector<unsigned char>>(cols, std::vector<unsigned char>(channels)));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            flipped_image[i][j] = image_data[i][cols - j - 1];
        }
    }

    saveImage(flipped_image, "flipped_image_horizontal.jpg", rows, cols);
}

void ImageProcessor::flipVertical() {
    std::vector<std::vector<std::vector<unsigned char>>> flipped_image(rows,
        std::vector<std::vector<unsigned char>>(cols, std::vector<unsigned char>(channels)));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            flipped_image[i][j] = image_data[rows - i - 1][j];
        }
    }

    saveImage(flipped_image, "flipped_image_vertical.jpg", rows, cols);
}

void ImageProcessor::rotate90() {
    int original_rows = rows;
    int original_cols = cols;

    std::vector<std::vector<std::vector<unsigned char>>> rotated_image(original_cols,
        std::vector<std::vector<unsigned char>>(original_rows, std::vector<unsigned char>(channels)));

    for (int i = 0; i < original_rows; ++i) {
        for (int j = 0; j < original_cols; ++j) {
            rotated_image[j][original_rows - i - 1] = image_data[i][j]; 
        }
    }

    rows = original_cols;
    cols = original_rows;

    saveImage(rotated_image, "rotated_image_90.jpg", rows, cols);
}

void ImageProcessor::saveImage(const std::vector<std::vector<std::vector<unsigned char>>>& img_data, const std::string& outputPath, int final_rows, int final_cols) {
    cv::Mat output(final_rows, final_cols, CV_8UC3);

    for (int i = 0; i < final_rows; ++i) {
        for (int j = 0; j < final_cols; ++j) {
            output.at<cv::Vec3b>(i, j)[0] = img_data[i][j][0];
            output.at<cv::Vec3b>(i, j)[1] = img_data[i][j][1];
            output.at<cv::Vec3b>(i, j)[2] = img_data[i][j][2];
        }
    }

    cv::imwrite(outputPath, output);
}
