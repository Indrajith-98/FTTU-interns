#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>

class ImageProcessor
{
public:
    ImageProcessor(const std::string &imagePath)
    {
        image = cv::imread(imagePath, cv::IMREAD_COLOR);
        if (image.empty())
        {
            std::cerr << "Error: Could not open or find the image!" << std::endl;
            exit(1);
        }
        height = image.rows;
        width = image.cols;
        channels = image.channels();
        data.resize(height, std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(channels)));
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                cv::Vec3b color = image.at<cv::Vec3b>(y, x);
                for (int c = 0; c < channels; c++)
                {
                    data[y][x][c] = color[c];
                }
            }
        }
    }

    void toGrayscale()
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                unsigned char gray = static_cast<unsigned char>(0.299 * data[y][x][2] +
                                                                0.587 * data[y][x][1] +
                                                                0.114 * data[y][x][0]);
                data[y][x] = {gray, gray, gray};
            }
        }
    }

    void invertColors()
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                for (int c = 0; c < channels; c++)
                {
                    data[y][x][c] = 255 - data[y][x][c];
                }
            }
        }
    }

    void blurImage(int kernelSize = 3)
    {
        int offset = kernelSize / 2;
        auto blurredData = data;
        for (int y = offset; y < height - offset; y++)
        {
            for (int x = offset; x < width - offset; x++)
            {
                std::vector<int> sum(channels, 0);
                for (int ky = -offset; ky <= offset; ky++)
                {
                    for (int kx = -offset; kx <= offset; kx++)
                    {
                        for (int c = 0; c < channels; c++)
                        {
                            sum[c] += data[y + ky][x + kx][c];
                        }
                    }
                }
                for (int c = 0; c < channels; c++)
                {
                    blurredData[y][x][c] = sum[c] / (kernelSize * kernelSize);
                }
            }
        }
        data = blurredData;
    }

    void edgeDetection()
    {
        auto edgeData = data;
        std::vector<std::vector<unsigned char>> grayImage(height, std::vector<unsigned char>(width));

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                grayImage[y][x] = static_cast<unsigned char>(0.299 * data[y][x][2] +
                                                             0.587 * data[y][x][1] +
                                                             0.114 * data[y][x][0]);
            }
        }

        for (int y = 1; y < height - 1; y++)
        {
            for (int x = 1; x < width - 1; x++)
            {
                int gx = -grayImage[y - 1][x - 1] - 2 * grayImage[y][x - 1] - grayImage[y + 1][x - 1] +
                         grayImage[y - 1][x + 1] + 2 * grayImage[y][x + 1] + grayImage[y + 1][x + 1];

                int gy = -grayImage[y - 1][x - 1] - 2 * grayImage[y - 1][x] - grayImage[y - 1][x + 1] +
                         grayImage[y + 1][x - 1] + 2 * grayImage[y + 1][x] + grayImage[y + 1][x + 1];

                int magnitude = std::sqrt(gx * gx + gy * gy);
                magnitude = std::min(255, magnitude);
                edgeData[y][x] = {static_cast<unsigned char>(magnitude),
                                  static_cast<unsigned char>(magnitude),
                                  static_cast<unsigned char>(magnitude)};
            }
        }
        data = edgeData;
    }

    void resizeImage(int newWidth, int newHeight)
    {
        std::vector<std::vector<std::vector<unsigned char>>> resizedData(newHeight, std::vector<std::vector<unsigned char>>(newWidth, std::vector<unsigned char>(channels)));
        double xRatio = static_cast<double>(width) / newWidth;
        double yRatio = static_cast<double>(height) / newHeight;

        for (int y = 0; y < newHeight; y++)
        {
            for (int x = 0; x < newWidth; x++)
            {
                int px = static_cast<int>(x * xRatio);
                int py = static_cast<int>(y * yRatio);
                resizedData[y][x] = data[py][px];
            }
        }
        data = resizedData;
        width = newWidth;
        height = newHeight;
    }

    void saveImage(const std::string &outputPath)
    {
        cv::Mat outputImage(height, width, CV_8UC3);
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                for (int c = 0; c < channels; c++)
                {
                    outputImage.at<cv::Vec3b>(y, x)[c] = data[y][x][c];
                }
            }
        }
        cv::imwrite(outputPath, outputImage);
    }

private:
    cv::Mat image;
    int height, width, channels;
    std::vector<std::vector<std::vector<unsigned char>>> data;
};

int main()
{
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
