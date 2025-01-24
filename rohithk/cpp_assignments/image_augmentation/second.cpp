#include <image_processor.h>
#include <iostream>
using namespace std;
int main(int argc, char **argv) {
  Mat image = imread(
      "/home/rohithk/mcw/FTTU-interns/rohithk/cpp_assignment/second/cat.jpg");
  ImageProcessor image_augmentor = ImageProcessor();
  int choice = 0;
  cout << "0. Exit" << endl;
  cout << "1. Increase Brightness" << endl;
  cout << "2. Horizontal Flip" << endl;
  cout << "3. Vertical Flip" << endl;
  cout << "4. To Grayscale" << endl;
  cout << "5. Rotate Image 90" << endl;
  cout << "6. Rotate Image -90" << endl;
  cout << "7. Change contrast" << endl;
  cout << "Enter your choice: ";
  cin >> choice;
  while (choice != 0) {
    switch (choice) {
    case 1:
      image_augmentor.increaseBrightness(image);
      break;
    case 2:
      image_augmentor.horizontalFlipImage(image);
      break;
    case 3:
      image_augmentor.verticalFlipImage(image);
      break;
    case 4:
      image_augmentor.toGrayscale(image);
      break;
    case 5:
      image_augmentor.rotateImage90(image);
      break;
    case 6:
      image_augmentor.anRotateImage90(image);
      break;
    case 7:
      image_augmentor.contrastHandler(image);
      break;
    default:
      break;
    }
    cout << "Enter your choice: ";
    cin >> choice;
  }
  return 0;
}