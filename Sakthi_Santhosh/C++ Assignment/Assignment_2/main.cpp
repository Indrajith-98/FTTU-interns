#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <opencv2/opencv.hpp>  

template <typename T>
const T& custom_clamp(const T& value, const T& low, const T& high) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

class ImageProcessor {
private:
    unsigned char* data;         
    unsigned char* originalData;  
    int width, height, channels;

public:
   
    ImageProcessor(const std::string& filename) {
        loadImage(filename);
    }

   
    ~ImageProcessor() {
        delete[] data;
        delete[] originalData;
    }

    
    void loadImage(const std::string& filename) {
        cv::Mat img = cv::imread(filename, cv::IMREAD_COLOR); 
        
        if (img.empty()) {
            std::cerr << "Error loading image!" << std::endl;
            return;
        }

        width = img.cols;
        height = img.rows;
        channels = img.channels();


        originalData = new unsigned char[width * height * channels];
        data = new unsigned char[width * height * channels];

       
        std::memcpy(originalData, img.data, width * height * channels);
        std::memcpy(data, img.data, width * height * channels);

        std::cout << "Image loaded from " << filename << " (OpenCV loading)." << std::endl;
    }

   
    void saveImage(const std::string& filename) {
      
        cv::Mat img(height, width, CV_8UC3, data);

       
        if (cv::imwrite(filename, img)) {
            std::cout << "Image saved to " << filename << std::endl;
        } else {
            std::cout << "Failed to save image." << std::endl;
        }
    }

  
    void convertToGray() {
        unsigned char* grayData = new unsigned char[width * height * channels];

        for (int i = 0; i < width * height; ++i) {
            int r = data[i * channels];
            int g = data[i * channels + 1];
            int b = data[i * channels + 2];
            unsigned char gray = static_cast<unsigned char>(0.299 * r + 0.587 * g + 0.114 * b);

           
            grayData[i * channels] = gray;
            grayData[i * channels + 1] = gray;
            grayData[i * channels + 2] = gray;
        }

        delete[] data;
        data = grayData;
    }

    
    void flipHorizontal() {
        unsigned char* tempData = new unsigned char[width * height * channels];
        std::memcpy(tempData, originalData, width * height * channels);  

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width / 2; ++x) {
                int leftIndex = (y * width + x) * channels;
                int rightIndex = (y * width + (width - x - 1)) * channels;

               
                for (int c = 0; c < channels; ++c) {
                    std::swap(tempData[leftIndex + c], tempData[rightIndex + c]);
                }
            }
        }

        delete[] data;
        data = tempData; 
    }

    
    void flipVertical() {
        unsigned char* tempData = new unsigned char[width * height * channels];
        std::memcpy(tempData, originalData, width * height * channels);  

        unsigned char* tempRow = new unsigned char[width * channels];

        for (int y = 0; y < height / 2; ++y) {
            int topIndex = y * width * channels;
            int bottomIndex = (height - y - 1) * width * channels;

            
            std::memcpy(tempRow, tempData + topIndex, width * channels);
            std::memcpy(tempData + topIndex, tempData + bottomIndex, width * channels);
            std::memcpy(tempData + bottomIndex, tempRow, width * channels);
        }

        delete[] data;
        data = tempData;  
    }

        void adjustBrightness(int brightnessOffset) {
        unsigned char* tempData = new unsigned char[width * height * channels];
        std::memcpy(tempData, originalData, width * height * channels);  

        for (int i = 0; i < width * height * channels; ++i) {
            int newValue = tempData[i] + brightnessOffset;
            tempData[i] = static_cast<unsigned char>(custom_clamp(newValue, 0, 255));
        }

        delete[] data;
        data = tempData;  
    }

    void rotate(double angle) {
    unsigned char* tempData = new unsigned char[width * height * channels];
    std::memcpy(tempData, originalData, width * height * channels);  
    double radians = angle * 3.141592653589793 / 180.0;  
    double cosTheta = cos(radians);
    double sinTheta = sin(radians);

    int centerX = width / 2;
    int centerY = height / 2;

    unsigned char* rotatedData = new unsigned char[width * height * channels];
    std::memset(rotatedData, 0, width * height * channels);  

    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
           
            int newX = static_cast<int>((x - centerX) * cosTheta - (y - centerY) * sinTheta + centerX);
            int newY = static_cast<int>((x - centerX) * sinTheta + (y - centerY) * cosTheta + centerY);

      
            if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                for (int c = 0; c < channels; ++c) {
                    rotatedData[(newY * width + newX) * channels + c] = tempData[(y * width + x) * channels + c];
                }
            }
        }
    }

    delete[] data;
    data = rotatedData;  

    }

    
    void getImageDimensions(int& widthOut, int& heightOut, int& channelsOut) {
        widthOut = width;
        heightOut = height;
        channelsOut = channels;
    }
};

int main() {

    std::string filename ="D:/Santhosh@McW/C++ Assignment/Assignment_2/image.jpg";
    ImageProcessor processor(filename);

    int width, height, channels;
    processor.getImageDimensions(width, height, channels);

    std::cout << "Loaded image: " << width << "x" << height << " with " << channels << " channels." << std::endl;

    int choice;
    do {
        std::cout << "\nSelect an operation to perform:\n";
        std::cout << "1. Convert to Grayscale\n";
        std::cout << "2. Flip Horizontally\n";
        std::cout << "3. Flip Vertically\n";
        std::cout << "4. Adjust Brightness\n";
        std::cout << "5. Rotate Image\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                processor.convertToGray();
                processor.saveImage("grayscale_image.png");
                break;

            case 2:
                processor.flipHorizontal();
                processor.saveImage("flipped_horizontal.png");
                break;

            case 3:
                processor.flipVertical();
                processor.saveImage("flipped_vertical.png");
                break;

            case 4: {
                int offset;
                std::cout << "Enter brightness adjustment value: ";
                std::cin >> offset;
                processor.adjustBrightness(offset);
                processor.saveImage("brightness_adjusted.png");
                break;
            }

            case 5: {
                double angle;
                std::cout << "Enter rotation angle (in degrees): ";
                std::cin >> angle;
                processor.rotate(angle);
                processor.saveImage("rotated_image.png");
                break;
            }

            case 6:
                std::cout << "Exiting program." << std::endl;
                break;

            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 6);

    return 0;
}
