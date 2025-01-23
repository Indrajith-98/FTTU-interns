#include "image_processor.h"
#include "grayscale.h"
#include "negation.h"
#include "brightness.h"
#include "horizontal_flip.h"
#include "vertical_flip.h"
#include <iostream>

int main() {
    ImageProcessor processor;
    std::string input_image, output_image;
    int choice;

    input_image = "D:/Documents_personal/Multicoreware/training/Image_processing/flower.jpg";
    if (!processor.loadImage(input_image)) {
        return -1;
    }

    while (true) {
        std::cout << "\nImage Processing Menu:\n";
        std::cout << "1. Convert to Grayscale\n";
        std::cout << "2. Negate Image\n";
        std::cout << "3. Adjust Brightness\n";
        std::cout << "4. Flip Horizontally\n";
        std::cout << "5. Flip Vertically\n";
        std::cout << "6. Save Image\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                toGrayscale(processor);
                break;
            case 2:
                negateImage(processor);
                break;
            case 3: {
                int value;
                std::cout << "Enter brightness adjustment value (-255 to 255): ";
                std::cin >> value;
                adjustBrightness(processor, value);
                break;
            }
            case 4:
                flipHorizontal(processor);
                break;
            case 5:
                flipVertical(processor);
                break;
            case 6:
                std::cout << "Enter the path to save the processed image: ";
                std::cin >> output_image;
                processor.saveImage(output_image);
                break;
            case 7:
                std::cout << "Exiting the application." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice! Try again." << std::endl;
        }
    }

    return 0;
}
