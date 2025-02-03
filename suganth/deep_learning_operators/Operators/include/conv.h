#ifndef CONV_H
#define CONV_H

#include <vector>

class Convolution {
public:
    // Constructor to initialize kernel dimensions
    Convolution(int kernel_height, int kernel_width, int kernel_depth = 1);
    

    // Function to perform 2D convolution on an image using a 3D kernel (with multiple filters)
    std::vector<std::vector<double>> performConvolution(
        const std::vector<std::vector<std::vector<double>>>& input_image,int depth, int image_height, int image_width,
        const std::vector<std::vector<std::vector<double>>>& kernels,  // 3D kernel (filters)
        const double bias,
        int stride = 1, int padding = 0
    );

private:
    int kernel_height; // Height of the kernel
    int kernel_width;  // Width of the kernel
    int kernel_depth;  // Depth of the kernel (number of filters)
};


#endif // CONV_H
