# Image Preprocessing Technique

### About

This program applies image preprocessing techniques to the src image using cpp.

- 1. Grayscale Conversion
- 2. Rotation by angle
- 3. Vertical Flip
- 4. Zoom In
- 5. Sobel Edge detection

OpenCV Library is used to open and display the original and resultant images.

### Run the program

##### Create build directory

```
mkdir build
cd build
```

##### Build and Run

```
cmake ..
cmake --build .
./ImagePreprocessing.exe

```

### Output

```
Enter the angle (in degrees) to rotate the image: 60  

```

![Original Image](image_preprocessing_results/org.png "Original Image")
![Grayscale converted Image](image_preprocessing_results/gs.png "Grayscale converted Image")
![Rotated by angle Image](image_preprocessing_results/ra.png "Rotated by angle Image")
![Vertically flipped Image](image_preprocessing_results/vf.png "Vertically flipped Image")
![Zoomed In Image](image_preprocessing_results/zi.png "Zoomed In Image")
![Edge Detected Image](image_preprocessing_results/ed.png "Edge Detected Image")