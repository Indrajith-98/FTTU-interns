#include <image_processor.h>
#include <iostream>

using namespace std;

ImageProcessor::ImageProcessor(){};

// Function to increase the brightness of an image
void ImageProcessor::increaseBrightness(Mat image) {
  // Clone the input image to avoid modifying the original
  cv::Mat brightenedImage = image.clone();

  // Brightness increment value
  int brightnessValue = 50;

  // Traverse each pixel in the image
  for (int y = 0; y < image.rows; y++) {
    for (int x = 0; x < image.cols; x++) {
      for (int c = 0; c < image.channels(); c++) {
        // Adjust the brightness and ensure the value stays in range [0, 255]
        brightenedImage.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(
            image.at<cv::Vec3b>(y, x)[c] + brightnessValue);
      }
    }
  }

  // Save the brightened image to disk
  saveImageToDisk(brightenedImage, "brightened.png");
}

// Function to flip an image horizontally
void ImageProcessor::horizontalFlipImage(Mat image) {
  // Clone the input image to create the flipped output
  Mat flippedImage = image.clone();

  // Traverse each pixel and swap horizontally
  for (int y = 0; y < image.rows; y++) {
    for (int x = 0; x < image.cols; x++) {
      // Copy the pixel from the opposite side horizontally
      flippedImage.at<Vec3b>(y, image.cols - x - 1) = image.at<Vec3b>(y, x);
    }
  }

  // Save the horizontally flipped image to disk
  saveImageToDisk(flippedImage, "hflipped.png");
}

// Function to flip an image vertically
void ImageProcessor::verticalFlipImage(Mat image) {
  // Clone the input image to create the flipped output
  Mat flippedImage = image.clone();

  // Traverse each pixel and swap vertically
  for (int y = 0; y < image.rows; y++) {
    for (int x = 0; x < image.cols; x++) {
      // Copy the pixel from the opposite side vertically
      flippedImage.at<Vec3b>(image.rows - y - 1, x) = image.at<Vec3b>(y, x);
    }
  }

  // Save the vertically flipped image to disk
  saveImageToDisk(flippedImage, "vflipped.png");
}

// Function to adjust the contrast of an image
void ImageProcessor::contrastHandler(Mat inputImage) {
  // Alpha controls contrast
  double alpha = 1.5;

  // Beta adjusts brightness
  double beta = 0.0;

  // Create an output image with the same size and type as the input
  cv::Mat outputImage = cv::Mat::zeros(inputImage.size(), inputImage.type());

  // Traverse each pixel and adjust contrast and brightness
  for (int y = 0; y < inputImage.rows; y++) {
    for (int x = 0; x < inputImage.cols; x++) {
      for (int c = 0; c < inputImage.channels(); c++) {
        uchar pixel = inputImage.at<cv::Vec3b>(y, x)[c];

        // Apply the contrast and brightness formula
        int newPixel = static_cast<int>(alpha * (pixel - 128) + 128 + beta);

        // Clip the values to the range [0, 255]
        newPixel = std::max(0, std::min(255, newPixel));

        // Assign the new pixel value
        outputImage.at<cv::Vec3b>(y, x)[c] = static_cast<uchar>(newPixel);
      }
    }
  }

  // Save the contrast-adjusted image to disk
  saveImageToDisk(outputImage, "contrast_adjusted.png");
}

// Function to convert an image to grayscale
void ImageProcessor::toGrayscale(Mat image) {
  // Create an empty grayscale image with the same size as the input
  Mat grayImage = Mat::zeros(image.size(), CV_8UC1);

  // Grayscale weights for red, green, and blue channels
  const float wR = 0.299f, wG = 0.587f, wB = 0.114f;

  // Traverse each pixel and compute its grayscale value
  for (int y = 0; y < image.rows; y++) {
    for (int x = 0; x < image.cols; x++) {
      Vec3b pixel = image.at<Vec3b>(y, x);
      uchar gray = saturate_cast<uchar>((wR * pixel[2]) + (wG * pixel[1]) +
                                        (wB * pixel[0]));
      grayImage.at<uchar>(y, x) = gray;
    }
  }

  // Save the grayscale image to disk
  saveImageToDisk(grayImage, "grayscale_image.png");
}

// Function to rotate an image 90 degrees clockwise
void ImageProcessor::rotateImage90(Mat image) {
  // Create a new image with swapped dimensions (width becomes height)
  Mat rotatedImage = Mat::zeros(image.cols, image.rows, image.type());

  // Traverse each pixel and reposition it for a 90-degree rotation
  for (int x = 0; x < image.cols; x++) {
    for (int y = 0; y < image.rows; y++) {
      rotatedImage.at<Vec3b>(x, image.rows - 1 - y) = image.at<Vec3b>(y, x);
    }
  }

  // Save the rotated image to disk
  saveImageToDisk(rotatedImage, "rotated_image_90.png");
}

// Function to save an image to disk
bool ImageProcessor::saveImageToDisk(const cv::Mat &image,
                                     const std::string &filename) {
  // Ensure the image is not empty
  if (image.empty()) {
    std::cerr << "Error: Image is empty, cannot save to disk!" << std::endl;
    return false;
  }

  // Attempt to save the image
  if (!cv::imwrite(filename, image)) {
    std::cerr << "Error: Unable to save the image to " << filename << "!"
              << std::endl;
    return false;
  }

  // Indicate success
  std::cout << "Image successfully saved to: " << filename << std::endl;
  return true;
}
// Function to rotate an image 90 degrees anti-clockwise
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