#include <iostream>
#include "Grayscale.h"
#include "Blur.h"
#include "EdgeDetection.h"
#include "Resize.h"
#include "Rotate.h"

int main() {
    // Load the original image
    std::string inputFile = "O:/Training Assignments/OpenCV/input_img.jpeg";

    // Apply Grayscale
    Grayscale grayscale(inputFile);
    grayscale.process();
    grayscale.save("O:/Training Assignments/OpenCV/output_grayscale.jpg");

    // Apply Blur on Grayscale image
    Blur blur("O:/Training Assignments/OpenCV/input_img.jpeg", 5);
    blur.process();
    blur.save("O:/Training Assignments/OpenCV/output_blurred.jpg");

    // Apply Edge Detection on Blurred image
    EdgeDetection edge("O:/Training Assignments/OpenCV/input_img.jpeg");
    edge.process();
    edge.save("O:/Training Assignments/OpenCV/output_edges.jpg");

    // Resize the image
    Resize resize("O:/Training Assignments/OpenCV/input_img.jpeg", 200, 200);
    resize.process();
    resize.save("O:/Training Assignments/OpenCV/output_resized.jpg");

    // Rotate the image
    Rotate rotate("O:/Training Assignments/OpenCV/input_img.jpeg");
    rotate.process();
    rotate.save("O:/Training Assignments/OpenCV/output_rotated.jpg");

    std::cout << "Processing completed" << std::endl;

}
