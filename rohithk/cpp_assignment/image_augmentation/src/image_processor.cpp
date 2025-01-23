#include <image_processor.h>
#include <iostream>

using namespace std;
ImageProcessor::ImageProcessor(){};

void ImageProcessor::increaseBrightness(Mat image) {
  cv::Mat brightenedImage = image.clone();

  int brightnessValue = 50;

  for (int y = 0; y < image.rows; y++) {
    for (int x = 0; x < image.cols; x++) {
      for (int c = 0; c < image.channels(); c++) {
        brightenedImage.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(
            image.at<cv::Vec3b>(y, x)[c] + brightnessValue);
      }
    }
  }

  saveImageToDisk(brightenedImage, "brightened.png");
}
void ImageProcessor::horizontalFlipImage(Mat image) {
  Mat flippedImage = image.clone();
  for (int y = 0; y < image.rows; y++) {
    for (int x = 0; x < image.cols; x++) {
      flippedImage.at<Vec3b>(y, image.cols - x - 1) = image.at<Vec3b>(y, x);
    }
  }

  saveImageToDisk(flippedImage, "hflipped.png");
}
void ImageProcessor::verticalFlipImage(Mat image) {
  Mat flippedImage = image.clone();
  for (int y = 0; y < image.rows; y++) {
    for (int x = 0; x < image.cols; x++) {
      flippedImage.at<Vec3b>(image.rows - y - 1, x) = image.at<Vec3b>(y, x);
    }
  }

  saveImageToDisk(flippedImage, "vflipped.png");
}
void ImageProcessor::toGrayscale(Mat image) {
  Mat grayImage = Mat::zeros(image.size(), CV_8UC1);
  int y, j;
  const float wR = 0.299f, wG = 0.587f, wB = 0.114f;
  for (int y = 0; y < image.rows; y++) {
    for (int x = 0; x < image.cols; x++) {
      Vec3b pixel = image.at<Vec3b>(y, x);
      uchar gray = saturate_cast<uchar>(
          (0.299 * pixel[2]) + (0.587 * pixel[1]) + (0.114 * pixel[0]));
      grayImage.at<uchar>(y, x) = gray;
    }
  }
  std::string outputPath = "grayscale_image.png";
  saveImageToDisk(grayImage, outputPath);
}
void ImageProcessor::rotateImage90(Mat image) {

  Mat rotatedImage = Mat::zeros(image.cols, image.rows, image.type());
  int z = 0;
  int m = 0;
  for (int x = 0; x < image.cols; x++) {
    for (int y = 0; y < image.rows; y++) {
      rotatedImage.at<Vec3b>(m, z) = image.at<Vec3b>(y, x);
      z += 1;
    }
    m += 1;
    z = 0;
  }
  saveImageToDisk(rotatedImage, "rotated_image_90.png");
}
void ImageProcessor::anRotateImage90(Mat image) {

  Mat rotatedImage = Mat::zeros(image.cols, image.rows, image.type());
  int z = 0;
  int m = 0;
  for (int x = 0; x < image.cols; x++) {
    for (int y = 0; y < image.rows; y++) {
      rotatedImage.at<Vec3b>(m, z) = image.at<Vec3b>(y, x);
      z += 1;
    }
    m += 1;
    z = 0;
  }
  saveImageToDisk(rotatedImage, "rotated_image_90.png");
}

bool ImageProcessor::saveImageToDisk(const cv::Mat &image,
                                     const std::string &filename) {
  if (image.empty()) {
    std::cerr << "Error: Image is empty, cannot save to disk!" << std::endl;
    return false;
  }

  if (!cv::imwrite(filename, image)) {
    std::cerr << "Error: Unable to save the image to " << filename << "!"
              << std::endl;
    return false;
  }

  std::cout << "Image successfully saved to: " << filename << std::endl;
  return true;
}