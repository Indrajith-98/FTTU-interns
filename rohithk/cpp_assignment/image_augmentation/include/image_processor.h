#ifndef IMAGE_PROCESSOR
#define IMAGE_PROCESSOR

#include <opencv2/opencv.hpp>
using namespace cv;

class ImageProcessor {
public:
  ImageProcessor();
  void increaseBrightness(Mat image);
  void horizontalFlipImage(Mat image);
  void verticalFlipImage(Mat image);
  void toGrayscale(Mat image);
  void rotateImage90(Mat image);
  void anRotateImage90(Mat image);
  void contrastHandler(Mat image);

private:
  bool saveImageToDisk(const cv::Mat &image, const std::string &filename);
};
#endif