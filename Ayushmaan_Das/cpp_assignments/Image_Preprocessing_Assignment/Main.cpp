#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
#include <direct.h>

using namespace std;
using namespace cv;

class ProcessImage
{
public:
    // METHOD TO CONVERT BACK 3D MATRIX TO OPENCV OBJECT (default format)
    static cv::Mat toMat(const std::vector<std::vector<std::vector<int>>> &img)
    {
        double rows = img.size();
        double cols = img[0].size();
        cv::Mat output(rows, cols, CV_8UC3);

        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < cols; ++x)
            {
                output.at<cv::Vec3b>(y, x)[0] = img[y][x][0];
                output.at<cv::Vec3b>(y, x)[1] = img[y][x][1];
                output.at<cv::Vec3b>(y, x)[2] = img[y][x][2];
            }
        }
        return output;
    }

    // INVERTING THE COLORS OF ORIGINAL IMAGE
    static void invertColors(std::vector<std::vector<std::vector<int>>> &img)
    {
        for (int y = 0; y < img.size(); ++y)
        {
            for (int x = 0; x < img[0].size(); ++x)
            {
                img[y][x][0] = 255 - img[y][x][0];
                img[y][x][1] = 255 - img[y][x][1];
                img[y][x][2] = 255 - img[y][x][2];
            }
        }
    }

    // ROTATING IMAGE BY SPECIFIED ANGLE
    static void rotateImage(std::vector<std::vector<std::vector<int>>> &img, double angle)
    {
        const double pi_value = 3.141592653589793238462643383279502884197;
        int rows = img.size();
        int cols = img[0].size();
        int centerX = cols / 2;
        int centerY = rows / 2;

        double radian = (angle * pi_value) / 180.0;
        double cosTheta = cos(radian);
        double sinTheta = sin(radian);

        std::vector<std::vector<std::vector<int>>> output(rows, std::vector<std::vector<int>>(cols, std::vector<int>(3, 0)));

        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < cols; ++x)
            {
                double newX = cosTheta * (x - centerX) - sinTheta * (y - centerY) + centerX;
                double newY = sinTheta * (x - centerX) + cosTheta * (y - centerY) + centerY;

                if (newX >= 0 && newX < cols && newY >= 0 && newY < rows)
                {
                    output[newY][newX] = img[y][x];
                }
            }
        }

        img = output;
    }

    // CONVERT RGB IMAGE TO GRAYSCALE
    static void convertToGrayscale(std::vector<std::vector<std::vector<int>>> &img)
    {
        for (int y = 0; y < img.size(); ++y)
        {
            for (int x = 0; x < img[0].size(); ++x)
            {
                int gray = static_cast<int>(0.299 * img[y][x][2] + 0.587 * img[y][x][1] + 0.114 * img[y][x][0]);
                img[y][x][0] = img[y][x][1] = img[y][x][2] = gray;
            }
        }
    }

    // INCREASING or DECREASING SIZE OF THE IMAGE
    static void scaleImage(std::vector<std::vector<std::vector<int>>> &img, double scaleFactor)
    {
        int rows = img.size();
        int cols = img[0].size();
        int newRows = static_cast<int>(rows * scaleFactor);
        int newCols = static_cast<int>(cols * scaleFactor);

        std::vector<std::vector<std::vector<int>>> output(newRows, std::vector<std::vector<int>>(newCols, std::vector<int>(3, 0)));

        for (int y = 0; y < newRows; ++y)
        {
            for (int x = 0; x < newCols; ++x)
            {
                int origY = static_cast<int>(y / scaleFactor);
                int origX = static_cast<int>(x / scaleFactor);
                if (origY < rows && origX < cols)
                {
                    output[y][x] = img[origY][origX];
                }
            }
        }

        img = output;
    }

    // APPLYING THRESHOLDING ----> Separating objects from the background
    static void applyThreshold(std::vector<std::vector<std::vector<int>>> &img, int thresholdValue)
    {
        for (int y = 0; y < img.size(); ++y)
        {
            for (int x = 0; x < img[0].size(); ++x)
            {
                int gray = img[y][x][0];
                int binary = (gray > thresholdValue) ? 255 : 0;
                img[y][x][0] = img[y][x][1] = img[y][x][2] = binary;
            }
        }
    }
};

int main()
{
    const size_t size = 1024;
    char buffer[size];
    string truncatedPath = "";

    // FOR RETRIEVING THE CURRENT WORKING DIRECTORY
    if (getcwd(buffer, size) != NULL)
    {
        string currentDir(buffer);
        size_t lastBackslash = currentDir.find_last_of('\\');
        size_t secondLastBackslash = currentDir.find_last_of('\\', lastBackslash - 1);
        truncatedPath = currentDir.substr(0, secondLastBackslash);
        truncatedPath = truncatedPath + "/sample.png";
    }
    else
    {
        cout << "Error retrieving current directory." << endl;
        return -1;
    }

    Mat image = imread(truncatedPath, IMREAD_COLOR);

    if (image.empty())
    {
        cout << "Error in loading the image" << endl;
        return -1;
    }

    // PRINTING IMAGE DIMENSIONS
    int rows = image.rows;
    int cols = image.cols;
    cout << "Image dimensions - Height: " << rows << " Width: " << cols << endl;

    // CONVERTING THE IMAGE (OpenCV Object) INTO A 3-D MATRIX
    std::vector<std::vector<std::vector<int>>> image_vector(rows, std::vector<std::vector<int>>(cols, std::vector<int>(3, 0)));
    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < cols; ++x)
        {
            cv::Vec3b color = image.at<cv::Vec3b>(y, x);
            image_vector[y][x][0] = color[0];
            image_vector[y][x][1] = color[1];
            image_vector[y][x][2] = color[2];
        }
    }

    // APPLYING ALL IMAGE PROCESING TECHNIQUES ONE BY ONE (to original image only)
    // NOTE: For every technique, a copy of original image is used, hence original iamge is untouched

    try
    {
        vector<vector<vector<int>>> image_vector1 = image_vector;
        ProcessImage::invertColors(image_vector1);
        cv::imwrite("inverted_color.png", ProcessImage::toMat(image_vector1));
        cout << "\nInverted colors successfully and saved as inverted_color.png." << endl;
    }
    catch (const exception &e)
    {
        cerr << "Error inverting colors: " << e.what() << endl;
    }

    try
    {
        vector<vector<vector<int>>> image_vector2 = image_vector;
        ProcessImage::convertToGrayscale(image_vector2);
        cv::imwrite("grayscale.png", ProcessImage::toMat(image_vector2));
        cout << "\nConverted to grayscale successfully and saved as grayscale.png." << endl;
    }
    catch (const exception &e)
    {
        cerr << "Error converting to grayscale: " << e.what() << endl;
    }

    try
    {
        vector<vector<vector<int>>> image_vector3 = image_vector;
        ProcessImage::rotateImage(image_vector3, 90);
        cv::imwrite("rotated.png", ProcessImage::toMat(image_vector3));
        cout << "\nRotated image successfully and saved as rotated.png." << endl;
    }
    catch (const exception &e)
    {
        cerr << "Error rotating image: " << e.what() << endl;
    }

    try
    {
        vector<vector<vector<int>>> image_vector4 = image_vector;
        ProcessImage::scaleImage(image_vector4, 0.3);
        cv::imwrite("scaled.png", ProcessImage::toMat(image_vector4));
        cout << "\nScaled image successfully and saved as scaled.png." << endl;
    }
    catch (const exception &e)
    {
        cerr << "Error scaling image: " << e.what() << endl;
    }

    try
    {
        vector<vector<vector<int>>> image_vector5 = image_vector;
        ProcessImage::applyThreshold(image_vector5, 100);
        cv::imwrite("thresholded.png", ProcessImage::toMat(image_vector5));
        cout << "\nApplied Threshold successfully and saved as thresholded.png." << endl;
    }
    catch (const exception &e)
    {
        cerr << "Error applying threshold: " << e.what() << endl;
    }
}