#include <opencv2/opencv.hpp>
int main() {
    cv::Mat image = cv::imread("C:/Users/7501/Desktop/ImageProcessing/Leaf.jpg");
    if (image.empty()) {
        std::cerr << "Failed to load image!" << std::endl;
        return -1;
    }
    cv::imshow("Image", image);
    cv::waitKey(0);
    return 0;
}
