#include <opencv2/opencv.hpp>
#include <iostream>
#include "image_operations.h"

int main() {
    // Path to input and output images
    std::string inputPath = "/Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/imageManipulation/image1.jpeg";  // Replace with your input image path
    std::string shadowOutputPath = "/Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/imageManipulation/modifiedImages/shadow_adjusted.jpg";
    std::string highlightOutputPath = "/Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/imageManipulation/modifiedImages/highlight_adjusted.jpg";
    std::string contrastOutputPath = "/Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/imageManipulation/modifiedImages/contrast_adjusted.jpg";
    std::string saturationOutputPath = "/Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/imageManipulation/modifiedImages/saturation_adjusted.jpg";
    std::string bgrToHsvOutputPath = "/Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/cpp_assignments/imageManipulation/modifiedImages/bgr_to_hsv_converted.jpg";


    // Read the image using OpenCV (as BGR by default)
    cv::Mat inputImage = cv::imread(inputPath, cv::IMREAD_COLOR);

    // Check if the image was loaded successfully
    if (inputImage.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return 1;
    }

    // Convert BGR to HSV
    cv::Mat bgrToHsvImage;
    convertBGRtoHSV(inputImage, bgrToHsvImage);
    cv::imwrite(bgrToHsvOutputPath, bgrToHsvImage);

    // Adjust shadows
    cv::Mat shadowAdjusted;
    float shadowFactor = 1.5; // Increase shadows (>1 to increase, <1 to decrease)
    adjustShadows(inputImage, shadowAdjusted, shadowFactor);
    cv::imwrite(shadowOutputPath, shadowAdjusted);

    // Adjust highlights
    cv::Mat highlightAdjusted;
    float highlightFactor = 0.7; // Reduce highlights (<1 to reduce, >1 to increase)
    adjustHighlights(inputImage, highlightAdjusted, highlightFactor);
    cv::imwrite(highlightOutputPath, highlightAdjusted);

    // Adjust contrast
    cv::Mat contrastAdjusted;
    float contrastFactor = 1.5; // Adjust contrast (>1 to increase, <1 to decrease)
    adjustContrast(inputImage, contrastAdjusted, contrastFactor);
    cv::imwrite(contrastOutputPath, contrastAdjusted);

    // Adjust saturation
    cv::Mat saturationAdjusted;
    float saturationFactor = 1.5; // Adjust saturation (>1 to increase, <1 to decrease)
    adjustSaturation(inputImage, saturationAdjusted, saturationFactor);
    cv::imwrite(saturationOutputPath, saturationAdjusted);

    std::cout << "Image adjustments completed successfully!" << std::endl;
    return 0;
}
