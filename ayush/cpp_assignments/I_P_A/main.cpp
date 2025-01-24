#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using namespace cv;

// Class to handle custom image processing operations
class ProcessImage
{
public:
    // Invert colors
    static void invertColors(vector<vector<vector<int>>> &img)
    {
        for (int y = 0; y < img.size(); ++y)
        {
            for (int x = 0; x < img[0].size(); ++x)
            {
                img[y][x][0] = 255 - img[y][x][0]; // Red
                img[y][x][1] = 255 - img[y][x][1]; // Green
                img[y][x][2] = 255 - img[y][x][2]; // Blue
            }
        }
    }

    // Convert to grayscale
    static void convertToGrayscale(vector<vector<vector<int>>> &img)
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

    // Rotate image
    static void rotateImage(vector<vector<vector<int>>> &img, double angle)
    {
        const double pi = 3.14159265358979323846;
        int rows = img.size();
        int cols = img[0].size();
        int centerX = cols / 2;
        int centerY = rows / 2;

        double rad = angle * pi / 180;
        double cosTheta = cos(rad);
        double sinTheta = sin(rad);

        vector<vector<vector<int>>> result(rows, vector<vector<int>>(cols, vector<int>(3, 0)));

        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < cols; ++x)
            {
                int newX = static_cast<int>(cosTheta * (x - centerX) - sinTheta * (y - centerY) + centerX);
                int newY = static_cast<int>(sinTheta * (x - centerX) + cosTheta * (y - centerY) + centerY);

                if (newX >= 0 && newX < cols && newY >= 0 && newY < rows)
                {
                    result[newY][newX] = img[y][x];
                }
            }
        }
        img = result;
    }

    // Scale image
    static void scaleImage(vector<vector<vector<int>>> &img, double scaleFactor)
    {
        int rows = img.size();
        int cols = img[0].size();
        int newRows = static_cast<int>(rows * scaleFactor);
        int newCols = static_cast<int>(cols * scaleFactor);

        vector<vector<vector<int>>> result(newRows, vector<vector<int>>(newCols, vector<int>(3, 0)));

        for (int y = 0; y < newRows; ++y)
        {
            for (int x = 0; x < newCols; ++x)
            {
                int origY = static_cast<int>(y / scaleFactor);
                int origX = static_cast<int>(x / scaleFactor);
                if (origY < rows && origX < cols)
                {
                    result[y][x] = img[origY][origX];
                }
            }
        }
        img = result;
    }

    // Apply thresholding
    static void applyThreshold(vector<vector<vector<int>>> &img, int thresholdValue)
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

    // Convert vector to OpenCV Mat
    static Mat toMat(const vector<vector<vector<int>>> &img)
    {
        int rows = img.size();
        int cols = img[0].size();
        Mat result(rows, cols, CV_8UC3);

        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < cols; ++x)
            {
                result.at<Vec3b>(y, x)[0] = img[y][x][0];
                result.at<Vec3b>(y, x)[1] = img[y][x][1];
                result.at<Vec3b>(y, x)[2] = img[y][x][2];
            }
        }
        return result;
    }
};

int main()
{
    // Load the image using OpenCV
    Mat image = imread("C:\\Users\\sendm\\Desktop\\OneDriveBackupFiles\\Pictures\\whatapp\\PERSONAL\\fasinlif", IMREAD_COLOR);

    if (image.empty())
    {
        cout << "Could not load the image." << endl;
        return -1;
    }

    // Convert OpenCV Mat to 3D vector
    int rows = image.rows;
    int cols = image.cols;
    vector<vector<vector<int>>> img(rows, vector<vector<int>>(cols, vector<int>(3, 0)));

    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < cols; ++x)
        {
            Vec3b color = image.at<Vec3b>(y, x);
            img[y][x][0] = color[0];
            img[y][x][1] = color[1];
            img[y][x][2] = color[2];
        }
    }

    // Apply image processing operations
    ProcessImage::invertColors(img);
    imwrite("inverted.png", ProcessImage::toMat(img));

    ProcessImage::convertToGrayscale(img);
    imwrite("grayscale.png", ProcessImage::toMat(img));

    ProcessImage::rotateImage(img, 90);
    imwrite("rotated.png", ProcessImage::toMat(img));

    ProcessImage::scaleImage(img, 0.5);
    imwrite("scaled.png", ProcessImage::toMat(img));

    ProcessImage::applyThreshold(img, 100);
    imwrite("thresholded.png", ProcessImage::toMat(img));

    return 0;
}
