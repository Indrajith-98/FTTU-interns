#include <opencv2/opencv.hpp>
#include <iostream>

class ImageProcessor {
public:
    ImageProcessor(const std::string& imagePath) {

        image = cv::imread(imagePath, cv::IMREAD_COLOR);
        if (image.empty()) {
            std::cerr << "Error: Could not open or find the image!" << std::endl;
            exit(1);
        }
    }

    void toGrayscale() {
        cv::Mat grayImage(image.rows, image.cols, CV_8UC1);
        for (int y = 0; y < image.rows; y++) {
            for (int x = 0; x < image.cols; x++) {
                cv::Vec3b color = image.at<cv::Vec3b>(y, x);
                int gray = static_cast<int>(0.299 * color[2] + 0.587 * color[1] + 0.114 * color[0]);
                grayImage.at<uchar>(y, x) = gray;
            }
        }
        image = grayImage;
    }

    void invertColors() {
        for (int y = 0; y < image.rows; y++) {
            for (int x = 0; x < image.cols; x++) {
                cv::Vec3b& color = image.at<cv::Vec3b>(y, x);
                color[0] = 255 - color[0];
                color[1] = 255 - color[1];
                color[2] = 255 - color[2];
            }
        }
    }

    void blurImage(int kernelSize = 3) {
        cv::Mat blurredImage = image.clone();
        int offset = kernelSize / 2;
        for (int y = offset; y < image.rows - offset; y++) {
            for (int x = offset; x < image.cols - offset; x++) {
                cv::Vec3b sum = {0, 0, 0};
                for (int ky = -offset; ky <= offset; ky++) {
                    for (int kx = -offset; kx <= offset; kx++) {
                        sum += image.at<cv::Vec3b>(y + ky, x + kx);
                    }
                }
                blurredImage.at<cv::Vec3b>(y, x) = sum / (kernelSize * kernelSize);
            }
        }
        image = blurredImage;
    }

    void edgeDetection() {
        cv::Mat edges(image.rows, image.cols, CV_8UC1);
        cv::Mat grayImage;
        cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
        for (int y = 1; y < grayImage.rows - 1; y++) {
            for (int x = 1; x < grayImage.cols - 1; x++) {
                int gx = -grayImage.at<uchar>(y - 1, x - 1) - 2 * grayImage.at<uchar>(y, x - 1) - grayImage.at<uchar>(y + 1, x - 1)
                         + grayImage.at<uchar>(y - 1, x + 1) + 2 * grayImage.at<uchar>(y, x + 1) + grayImage.at<uchar>(y + 1, x + 1);
                int gy = -grayImage.at<uchar>(y - 1, x - 1) - 2 * grayImage.at<uchar>(y - 1, x) - grayImage.at<uchar>(y - 1, x + 1)
                         + grayImage.at<uchar>(y + 1, x - 1) + 2 * grayImage.at<uchar>(y + 1, x) + grayImage.at<uchar>(y + 1, x + 1);
                int magnitude = std::sqrt(gx * gx + gy * gy);
                edges.at<uchar>(y, x) = magnitude > 255 ? 255 : magnitude;
            }
        }
        image = edges;
    }

    void resizeImage(int newWidth, int newHeight) {
        cv::Mat resizedImage(newHeight, newWidth, image.type());
        double xRatio = static_cast<double>(image.cols) / newWidth;
        double yRatio = static_cast<double>(image.rows) / newHeight;
        for (int y = 0; y < newHeight; y++) {
            for (int x = 0; x < newWidth; x++) {
                int px = static_cast<int>(x * xRatio);
                int py = static_cast<int>(y * yRatio);
                resizedImage.at<cv::Vec3b>(y, x) = image.at<cv::Vec3b>(py, px);
            }
        }
        image = resizedImage;
    }

    void saveImage(const std::string& outputPath) {
        cv::imwrite(outputPath, image);
    }

private:
    cv::Mat image;
};

int main() {
    ImageProcessor processor("D:/MCW/Assignment-3 CPP/ImageProcessing/Images/Input Image/input.jpg");
    processor.toGrayscale();
    processor.saveImage("D:/MCW/Assignment-3 CPP/ImageProcessing/Images/Output Image/output_grayscale.jpg");

    processor = ImageProcessor("D:/MCW/Assignment-3 CPP/ImageProcessing/Images/Input Image/input.jpg");
    processor.invertColors();
    processor.saveImage("D:/MCW/Assignment-3 CPP/ImageProcessing/Images/Output Image/output_inverted.jpg");

    processor = ImageProcessor("D:/MCW/Assignment-3 CPP/ImageProcessing/Images/Input Image/input.jpg");
    processor.blurImage();
    processor.saveImage("D:/MCW/Assignment-3 CPP/ImageProcessing/Images/Output Image/output_blurred.jpg");

    processor = ImageProcessor("D:/MCW/Assignment-3 CPP/ImageProcessing/Images/Input Image/input.jpg");
    processor.edgeDetection();
    processor.saveImage("D:/MCW/Assignment-3 CPP/ImageProcessing/Images/Output Image/output_edges.jpg");

    processor = ImageProcessor("D:/MCW/Assignment-3 CPP/ImageProcessing/Images/Input Image/input.jpg");
    processor.resizeImage(200, 200);
    processor.saveImage("D:/MCW/Assignment-3 CPP/ImageProcessing/Images/Output Image/output_resized.jpg");
    std::cout << "All processes done!" << std::endl;
    return 0;
}