# Image Processor

This is a command-line image processing application that supports several basic image manipulation operations. It uses the FreeImage library for image loading and saving.

## Features

- **Command-line interface:** Operate the application using command-line arguments.
- **Supported operations:**
  - Grayscale conversion
  - Gaussian blur
  - Sharpening
  - Thresholding
  - Edge detection
- **Input format:** Supports 24-bit BMP images (no alpha channel).
- **Help message:** Displays usage instructions via the `-h` option.

## Building

This project requires the FreeImage library. Make sure you have it installed and linked correctly in your build environment.

1.  **Clone the repository:**
    ```bash
    git clone <repository_url>
    cd <repository_directory>
    ```
2.  **Compile the code:**
    Use a C++ compiler that supports C++11 or later. For example, using g++:
    ```bash
    g++ -o ImageProcessor ImageProcessor.cpp getopt.cpp imgmanip.cpp -lfreeimage
    ```
    _Note:_ You might need to adjust the `-lfreeimage` flag based on how FreeImage is installed on your system. You may also need to include the path to the FreeImage headers using `-I/path/to/freeimage/include`.

## Usage

```
ImageProcessor -o <operation> -f <file>
```

### Options

- `-h`: Show help message.
- `-o <operation>`: Specify the operation to perform. Available operations are:
  - `grayscale`: Convert the image to grayscale.
  - `blur`: Apply a Gaussian blur effect.
  - `sharpen`: Enhance image sharpness.
  - `threshold`: Apply binary thresholding.
  - `edge`: Detect edges in the image.
- `-f <file>`: Specify the input file path (must be a 24-bit BMP file).

### Examples

```bash
# Convert an image to grayscale
ImageProcessor -o grayscale -f input.bmp

# Apply a blur effect
ImageProcessor -o blur -f input.bmp

# Detect edges in an image
ImageProcessor -o edge -f input.bmp

# Show help message
ImageProcessor -h
```

## Code Structure

- `ImageProcessor.cpp`: Main application file, handles command-line arguments and calls image processing functions.
- `imgmanip.h`: Header file declaring image manipulation functions.
- `imgmanip.cpp`: Implementation of image manipulation functions.
- `getopt.h` and `getopt.cpp`: Implementation of the `getopt` function for parsing command-line arguments.

## Dependencies

- [FreeImage](https://freeimage.sourceforge.io/): A library for image loading and saving.

## Notes

- The input image must be a 24-bit BMP file without an alpha channel.
- Output files are named `sample-<operation>.bmp` and are saved in the same directory as the executable.

## License

This project is provided as-is, without warranty. Please refer to the FreeImage license for the licensing of the FreeImage library.
