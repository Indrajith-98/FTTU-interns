#include <iostream>
#include "ImageProcessor.h"

int main() {
    std::string imagePath;
    std::cout << "Enter the image path: ";
    std::cin >> imagePath;
    ImageProcessor processor(imagePath);
    
    int choice;
    do {
        std::cout << "\nSelect the image processing operation:\n";
        std::cout << "1. Convert to Grayscale\n";
        std::cout << "2. Resize Image\n";
        std::cout << "3. Flip Image Horizontally\n";
        std::cout << "4. Flip Image Vertically\n";
        std::cout << "5. Rotate Image 90 Degrees\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                processor.toGrayscale();
                break;
            case 2:
                int new_width, new_height;
                std::cout << "Enter new width and height: ";
                std::cin >> new_width >> new_height;
                processor.resize(new_width, new_height);
                break;
            case 3:
                processor.flipHorizontal();
                break;
            case 4:
                processor.flipVertical();
                break;
            case 5:
                processor.rotate90();
                break;
            case 6:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
