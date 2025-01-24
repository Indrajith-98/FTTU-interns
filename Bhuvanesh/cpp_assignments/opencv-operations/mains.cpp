#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class mains{
    public:
        void convertToGrayscale(const Mat& inputImage, Mat& grayImage) {
            int width = inputImage.cols;
            int height = inputImage.rows;
            int channels = inputImage.channels(); 

            grayImage = Mat(height, width, CV_8UC1);

            uchar* inputPtr = inputImage.data;
            uchar* outputPtr = grayImage.data;

            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    int index = (i * width + j) * channels;

                    uchar blue = inputPtr[index];
                    uchar green = inputPtr[index + 1];
                    uchar red = inputPtr[index + 2];

                    outputPtr[i * width + j] = static_cast<uchar>(0.299 * red + 0.587 * green + 0.114 * blue);
                }
            }
        }
        void flipImageHorizontal(const Mat& inputImage, Mat& flippedImage) {
            int width = inputImage.cols;
            int height = inputImage.rows;
            int channels = inputImage.channels();

            flippedImage = Mat(height, width, inputImage.type());

            uchar* inputPtr = inputImage.data;
            uchar* outputPtr = flippedImage.data;

            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    int inputIndex = (i * width + j) * channels;
                    int outputIndex = (i * width + (width - j - 1)) * channels;

                    for (int k = 0; k < channels; k++) {
                        outputPtr[outputIndex + k] = inputPtr[inputIndex + k];
                    }
                }
            }
        }
        void applyBlur(const Mat& inputImage, Mat& blurredImage, int kernelSize) {
            int width = inputImage.cols;
            int height = inputImage.rows;
            int channels = inputImage.channels();

            blurredImage = Mat::zeros(height, width, inputImage.type());

            uchar* inputPtr = inputImage.data;
            uchar* outputPtr = blurredImage.data;

            int radius = kernelSize / 2;

            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    for (int k = 0; k < channels; k++) {
                        int sum = 0;
                        int count = 0;

                        for (int m = -radius; m <= radius; m++) {
                            for (int n = -radius; n <= radius; n++) {
                                int neighbor_i = i + m;
                                int neighbor_j = j + n;

                                if (neighbor_i >= 0 && neighbor_i < height && neighbor_j >= 0 && neighbor_j < width) {
                                    int index = (neighbor_i * width + neighbor_j) * channels + k;
                                    sum += inputPtr[index];
                                    count++;
                                }
                            }
                        }

                        int outputIndex = (i * width + j) * channels + k;
                        outputPtr[outputIndex] = static_cast<uchar>(sum / count);
                    }
                }
            }
        }
        void increaseBrightness(const Mat& inputImage, Mat& brightImage, int brightnessValue) {
            
            int width = inputImage.cols;
            int height = inputImage.rows;
            int channels = inputImage.channels(); 

            brightImage = Mat(height, width, inputImage.type()); // keeping the same type as input image
            
            uchar* inputPtr = inputImage.data;
            uchar* outputPtr = brightImage.data;

            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    int index = (i * width + j) * channels;

                    for (int c = 0; c < channels; c++) {
                        int val = inputPtr[index + c] + brightnessValue;
                        outputPtr[index + c] = static_cast<uchar>((val > 255) ? 255 : ((val < 0) ? 0 : val)); // handling both upper and lower bounds
                    }
                }
            }
        }
        void resizeImage(const Mat& inputImage, Mat& resizedImage, int newWidth, int newHeight) {
            int originalWidth = inputImage.cols;
            int originalHeight = inputImage.rows;
            int channels = inputImage.channels();

            // Create a new Mat to store the resized image
            resizedImage = Mat(newHeight, newWidth, inputImage.type());

            float x_ratio = static_cast<float>(originalWidth) / newWidth;
            float y_ratio = static_cast<float>(originalHeight) / newHeight;

            uchar* inputPtr = inputImage.data;
            uchar* outputPtr = resizedImage.data;

            // Resize using nearest-neighbor interpolation
            for (int i = 0; i < newHeight; i++) {
                for (int j = 0; j < newWidth; j++) {
                    int x = static_cast<int>(j * x_ratio);  // Find the corresponding x in the original image
                    int y = static_cast<int>(i * y_ratio);  // Find the corresponding y in the original image

                    int originalIndex = (y * originalWidth + x) * channels;
                    int newIndex = (i * newWidth + j) * channels;

                    // Copy pixel data from original image to resized image
                    for (int c = 0; c < channels; c++) {
                        outputPtr[newIndex + c] = inputPtr[originalIndex + c];
                    }
                }
            }
        }
};

int main(){

     string inputFilename = "D:/opencv-operations/input.jpg";
    Mat inputImage = imread(inputFilename, IMREAD_COLOR);
    int height,width,brightness;
    cout<<"Enter the height and width of the image to be resized and brightness one by one"<<endl;
    cin>>height>>width>>brightness;

    if (inputImage.empty()) {
        cerr << "Error: Could not open or find the image!" << endl;
        return -1;
    }

    cout << "Successfully read the image: " << inputFilename << endl;

    Mat grayImage,flipImage,blurImage,brightimage,resizeimage;

    mains obj;

    obj.convertToGrayscale(inputImage, grayImage);
    obj.flipImageHorizontal(inputImage, flipImage);
    obj.applyBlur(inputImage,blurImage,10);
    obj.increaseBrightness(inputImage,brightimage,brightness);
    obj.resizeImage(inputImage,resizeimage,width,height);
    string outputFilename = "D:/opencv-operations/output_gray.jpg";
    imwrite(outputFilename, grayImage);
    cout << "Grayscale image saved as: " << outputFilename << endl;

    outputFilename = "D:/opencv-operations/output_flip.jpg";
    imwrite(outputFilename, flipImage);
    cout << "Horizontal Flip image saved as: " << outputFilename << endl;

    outputFilename = "D:/opencv-operations/output_blur.jpg";
    imwrite(outputFilename, blurImage);
    cout << "The blurred image saved as: " << outputFilename << endl;

    outputFilename = "D:/opencv-operations/output_brightness.jpg";
    imwrite(outputFilename, brightimage);
    cout << "The brightened image saved as: " << outputFilename << endl;

    outputFilename = "D:/opencv-operations/output_resize.jpg";
    imwrite(outputFilename, resizeimage);
    cout << "The resized image saved as: " << outputFilename << endl;


    

    return 0;
    

}