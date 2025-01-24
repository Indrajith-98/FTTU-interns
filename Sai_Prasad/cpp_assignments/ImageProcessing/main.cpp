#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class ImageProcessing{
    public:
        void convertToGrayscale(const Mat& inputImage, Mat& grayImage) {
            
            int width = inputImage.cols;
            int height = inputImage.rows;
            int channels = inputImage.channels(); 

            grayImage = Mat(height, width, CV_8UC1); 
            
            uchar* inputPtr = inputImage.data;
            uchar* outputPtr = grayImage.data;

            for (int i=0; i<height; i++) {
                for (int j=0; j<width; j++) {
                    int index = (i * width + j) * channels;

                    uchar blue = inputPtr[index];
                    uchar green = inputPtr[index + 1];
                    uchar red = inputPtr[index + 2];

                    outputPtr[i * width + j] = static_cast<uchar>(0.299 * red + 0.587 * green + 0.114 * blue);
                }
            }
        }

        void adjustBrightness(const Mat& inputImage, Mat& brightImage, int brightnessValue){

            int width = inputImage.cols;
            int height = inputImage.rows;
            int channels = inputImage.channels();

            brightImage = Mat(height, width, inputImage.type()); 

            uchar* inputPtr = inputImage.data;
            uchar* outputPtr = brightImage.data;

           for (int i=0; i<height; i++) {
                for (int j=0; j<width; j++) {
                    int index = (i * width + j) * channels;

                    for(int c=0;c<channels;c++){
                        int val = inputPtr[index + c] + brightnessValue;
                        outputPtr[index + c] = static_cast<uchar>((val > 255) ? 255 : (val < 0 ? 0 : val));
                    }
                }
           } 
        }

        void resizeImage(const Mat& inputImage, Mat& resizedImage, int newWidth, int newHeight) {

            int originalWidth = inputImage.cols;
            int originalHeight = inputImage.rows;
            int channels = inputImage.channels();

            resizedImage = Mat(newHeight, newWidth, inputImage.type()); 

            float x_ratio = static_cast<float>(originalWidth) / newWidth;
            float y_ratio = static_cast<float>(originalHeight) / newHeight;

            uchar* inputPtr = inputImage.data;
            uchar* outputPtr = resizedImage.data;

            for (int i=0; i<newHeight; i++) {
                for (int j=0; j < newWidth; j++) {
                    int originalx = static_cast<int>(j * x_ratio);  
                    int originaly = static_cast<int>(i * y_ratio);  

                    int originalIndex = (originaly * originalWidth + originalx) * channels;
                    int newIndex = (i * newWidth + j) * channels;

                    for (int c= 0; c < channels; c++) {
                        outputPtr[newIndex + c] = inputPtr[originalIndex + c];
                    }
                }
            }
        }

        void flipHorizontal(const Mat& inputImage, Mat& flippedImage) {
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

            for (int i=0; i<height; i++) {
                for (int j=0; j<width; j++) {
                    for (int k=0; k<channels; k++) {
                        int sum = 0;
                        int count = 0;

                        for (int m=-radius; m<=radius; m++) {
                            for (int n=-radius; n<=radius; n++) {
                                int neighbor_i = i + m;
                                int neighbor_j = j + n;

                                if (neighbor_i>=0 && neighbor_i<height && neighbor_j>=0 && neighbor_j<width) {
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
};

int main(){

    string inputFilename = "D:/ImageProcessing/input.jpg";
    Mat inputImage = imread(inputFilename, IMREAD_COLOR);

    if (inputImage.empty()) {
        cerr << "Error: Could not open or find the image!" << endl;
        return -1;
    }

    cout << "Successfully read the image: " << inputFilename << endl;

    int brightnessValue;
    int resizeWidth, resizeHeight;

    Mat grayImage;
    Mat brightImage;
    Mat resizedImage;
    Mat FlippedImage;
    Mat BlurredImage;

    ImageProcessing obj;

    obj.convertToGrayscale(inputImage, grayImage);
    string outputGrayFilename = "D:/ImageProcessing/output_gray.jpg";
    imwrite(outputGrayFilename, grayImage);

    cout << "Enter the value for adjusting brightness (Enter negative value for decreasing, else just enter value for increasing): ";
    cin >> brightnessValue;

    obj.adjustBrightness(inputImage, brightImage, brightnessValue);
    string outputBrightFilename = "D:/ImageProcessing/output_bright.jpg";
    imwrite(outputBrightFilename, brightImage);

    cout << "Enter the new width and height for resizing the image: ";
    cin >> resizeWidth >> resizeHeight;

    obj.resizeImage(inputImage, resizedImage, resizeWidth, resizeHeight);
    string outputResizedFilename = "D:/ImageProcessing/output_resized.jpg";
    imwrite(outputResizedFilename, resizedImage);

    obj.flipHorizontal(inputImage, FlippedImage);
    string outputFlippedFilename = "D:/ImageProcessing/output_flipped.jpg";
    imwrite(outputFlippedFilename, FlippedImage);

    obj.applyBlur(inputImage, BlurredImage, 7);
    string outputBlurredFilename = "D:/ImageProcessing/output_blurred.jpg";
    imwrite(outputBlurredFilename, BlurredImage);

    cout << "Grayscale image saved as: " << outputGrayFilename << endl;
    cout << "Brightness processed image saved as: " << outputBrightFilename << endl;
    cout << "Resized image saved as: " << outputResizedFilename << endl;
    cout << "Flipped image saved as: " << outputFlippedFilename << endl;
    cout << "Blurred image saved as: " << outputBlurredFilename << endl;

    return 0;
    

}