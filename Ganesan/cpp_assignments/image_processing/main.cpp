#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

class ImageProcessor {
private:
    std::vector<std::vector<std::vector<int>>> image; // 3D vector to store RGB values
    int width, height;

public:
    // Constructor to initialize the image dimensions
    ImageProcessor(int w, int h) : width(w), height(h) {
        image.resize(height, std::vector<std::vector<int>>(width, std::vector<int>(3, 0)));
    }

    // Function to load the image (using OpenCV for I/O)
    void loadImage(const std::string& filePath) {
        cv::Mat img = cv::imread(filePath);

        if (img.empty()) {
            std::cerr << "Error loading image!" << std::endl;
            return;
        }

        width = img.cols;
        height = img.rows;
        image.resize(height, std::vector<std::vector<int>>(width, std::vector<int>(3, 0)));

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cv::Vec3b pixel = img.at<cv::Vec3b>(i, j);
                image[i][j][0] = pixel[0]; // Blue
                image[i][j][1] = pixel[1]; // Green
                image[i][j][2] = pixel[2]; // Red
            }
        }
    }

    // Function to save the image (using OpenCV for I/O)
    void saveImage(const std::string& filePath) {
        cv::Mat img(height, width, CV_8UC3);

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                img.at<cv::Vec3b>(i, j) = cv::Vec3b(image[i][j][0], image[i][j][1], image[i][j][2]);
            }
        }

        cv::imwrite(filePath, img);
    }

    // Grayscale conversion
    void toGrayscale() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int gray = 0.209 * image[i][j][2] + 0.587 * image[i][j][1] + 0.114 * image[i][j][0];
                image[i][j][0] = image[i][j][1] = image[i][j][2] = gray;
            }
        }
    }

    // Resize image using nearest-neighbor interpolation
    void resizeImage(int newWidth, int newHeight) {
        std::vector<std::vector<std::vector<int>>> newImage(newHeight, std::vector<std::vector<int>>(newWidth, std::vector<int>(3, 0)));

        for (int i = 0; i < newHeight; i++) {
            for (int j = 0; j < newWidth; j++) {
                int origX = j * width / newWidth;
                int origY = i * height / newHeight;
                newImage[i][j] = image[origY][origX];
            }
        }

        width = newWidth;
        height = newHeight;
        image = newImage;
    }

    // Simple edge detection using the Sobel operator
    void detectEdges() {
        std::vector<std::vector<std::vector<int>>> edgeImage = image;

        // Sobel operator kernel
        int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
        int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

        for (int i = 1; i < height - 1; i++) {
            for (int j = 1; j < width - 1; j++) {
                int gradX = 0, gradY = 0;
                for (int k = -1; k <= 1; k++) {
                    for (int l = -1; l <= 1; l++) {
                        int pixelValue = image[i + k][j + l][0]; // Use the red channel for simplicity
                        gradX += Gx[k + 1][l + 1] * pixelValue;
                        gradY += Gy[k + 1][l + 1] * pixelValue;
                    }
                }
                int grad = std::sqrt(gradX * gradX + gradY * gradY);
                grad = std::min(255, grad); // Clamping the value to [0, 255]
                edgeImage[i][j][0] = edgeImage[i][j][1] = edgeImage[i][j][2] = grad;
            }
        }

        image = edgeImage;
    }
    void histogramEqualization() {
        std::vector<int> hist(256, 0);

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int gray = image[i][j][0]; // Since it's grayscale
                hist[gray]++;
            }
        }

        std::vector<int> cdf(256, 0);
        cdf[0] = hist[0];
        for (int i = 1; i < 256; i++) {
            cdf[i] = cdf[i - 1] + hist[i];
        }

        int totalPixels = width * height;
        for (int i = 0; i < 256; i++) {
            cdf[i] = (cdf[i] * 255) / totalPixels;
        }

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int gray = image[i][j][0];
                int newGray = cdf[gray];
                image[i][j][0] = image[i][j][1] = image[i][j][2] = newGray;
            }
        }
    }

    // Image Sharpening
    void sharpenImage() {
        int kernel[3][3] = {
            { 0, -1,  0},
            {-1,  5, -1},
            { 0, -1,  0}
        };

        std::vector<std::vector<std::vector<int>>> sharpenedImage = image;

        for (int i = 1; i < height - 1; i++) {
            for (int j = 1; j < width - 1; j++) {
                for (int c = 0; c < 3; c++) {
                    int newValue = 0;
                    for (int k = -1; k <= 1; k++) {
                        for (int l = -1; l <= 1; l++) {
                            newValue += image[i + k][j + l][c] * kernel[k + 1][l + 1];
                        }
                    }
                    sharpenedImage[i][j][c] = std::min(255, std::max(0, newValue));
                }
            }
        }

        image = sharpenedImage;
    }
    // Display the image (for debugging)
    void displayImage() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                std::cout << "(" << image[i][j][0] << "," << image[i][j][1] << "," << image[i][j][2] << ") ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    ImageProcessor processor(0, 0);

    // Load an image
    processor.loadImage("C:\\Users\\prasa\\Downloads\\opencv_pro\\img\\cards.jpg");

    // Perform operations on the image grayscale, resize, edge detection
    processor.toGrayscale();
    processor.saveImage("grayscale_image.jpg");

    processor.resizeImage(3840,2160);
    processor.saveImage("resized_image.jpg");

    processor.detectEdges();
    processor.saveImage("edge_detected_image.jpg");

    processor.histogramEqualization();
    processor.saveImage("histogram_equalized_image.jpg");

    processor.sharpenImage();  
    processor.saveImage("sharpened_image.jpg");

    return 0;
}