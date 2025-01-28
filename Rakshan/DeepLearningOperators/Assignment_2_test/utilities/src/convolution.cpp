// #include "convolution.h"
// #include <fstream>
// #include <iostream>
// #include <cmath>
// #include <algorithm>

// // Function to read binary data from a file
// //template <typename T>
// // void readBinaryFile(const std::string &filePath, std::vector<T> &data)
// // {
// //     std::ifstream file(filePath, std::ios::binary);
// //     if (!file.is_open())
// //     {
// //         std::cerr << "Error: Cannot open file " << filePath << std::endl;
// //         exit(EXIT_FAILURE);
// //     }
// //     file.seekg(0, std::ios::end);
// //     size_t size = file.tellg() / sizeof(T);
// //     file.seekg(0, std::ios::beg);
// //     data.resize(size);
// //     file.read(reinterpret_cast<char *>(data.data()), size * sizeof(T));
// //     file.close();
// // }

// // Perform convolution

// // Perform convolution
// void convolve(const std::vector<float> &input, const std::vector<float> &kernel,
//               const std::vector<float> &bias, std::vector<float> &output,
//               int inputWidth, int inputHeight, int inputChannels, int outputChannels,
//               int kernelSize, int stride, const std::string &padding)
// {
//     // Padding calculation based on 'same' or 'valid'
//     int pad = (padding == "same") ? kernelSize / 2 : 0;

//     // Output dimensions, assuming padding doesn't change input width and height for 'same'
//     int outputWidth = inputWidth;
//     int outputHeight = inputHeight;

//     // Resize output vector to match the required output size
//     output.resize(outputWidth * outputHeight * outputChannels);

//     for (int oc = 0; oc < outputChannels; ++oc)
//     {
//         for (int oh = 0; oh < outputHeight; ++oh)
//         {
//             for (int ow = 0; ow < outputWidth; ++ow)
//             {
//                 float sum = bias[oc];  // Start with the bias value for the output channel 
//                 for (int ic = 0; ic < inputChannels; ++ic)
//                 {
//                     for (int kh = 0; kh < kernelSize; ++kh)
//                     {
//                         for (int kw = 0; kw < kernelSize; ++kw)
//                         {
//                             // Calculate the corresponding input pixel (taking padding into account)
//                             int ih = oh * stride + kh - pad;
//                             int iw = ow * stride + kw - pad;

//                             // Check if the input coordinates are valid (within the input image dimensions)
//                             if (ih >= 0 && ih < inputHeight && iw >= 0 && iw < inputWidth)
//                             {
//                                 // Calculate indices for input and kernel vectors
//                                 int inputIdx = (ic * inputHeight + ih) * inputWidth + iw;
//                                 int kernelIdx = ((oc * inputChannels + ic) * kernelSize + kh) * kernelSize + kw;

//                                 // Ensure indices are within valid range before accessing vectors
//                                 if (inputIdx >= 0 && inputIdx < input.size() &&
//                                     kernelIdx >= 0 && kernelIdx < kernel.size())
//                                 {
//                                     sum += input[inputIdx] * kernel[kernelIdx];
                                    
//                                 }

//                             }
//                         }
//                     }
//                 }

//                 // Calculate output index
//                 int outputIdx = (oc * outputHeight + oh) * outputWidth + ow;
//                 // Ensure output index is valid before writing
//                 if (outputIdx >= 0 && outputIdx < output.size())
//                 {
//                     output[outputIdx] = sum;
//                 }
//             }
//         }
//     }
// }

// void applyReLU(std::vector<float> &data)
// {
//     for (float &value : data)
//     {
//         value = std::max(0.0f, value);
//     }
// }





#include "convolution.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <cassert>
#include <fstream>

void convolution(const std::vector<float>& input, const std::vector<float>& kernel,
            const std::vector<float>& bias, std::vector<float>& output,
            const std::array<int, 4>& input_shape, const std::array<int, 4>& output_shape,
            const std::array<int, 2>& kernel_size, const std::array<int, 2>& strides,
            const std::string& padding, const std::string& layer_name) {
    int batch = 1;
    int in_height = input_shape[1], in_width = input_shape[2], in_channels = input_shape[3];
    int out_height = output_shape[1], out_width = output_shape[2], out_channels = output_shape[3];
    int kernel_height = kernel_size[0], kernel_width = kernel_size[1];

    // std::cout<<kernel.size() << " "<< batch * in_height * in_width * in_channels<<"\n";

    // assert(input.size() == batch * in_height * in_width * in_channels);
    // assert(kernel.size() == kernel_height * kernel_width * in_channels * out_channels);
    // assert(bias.size() == out_channels);
    // assert(output.size() == batch * out_height * out_width * out_channels);
    //  std::cout<<"hhi";

    for (int b = 0; b < batch; ++b) {
        for (int h = 0; h < out_height; ++h) {
            for (int w = 0; w < out_width; ++w) {
                for (int c = 0; c < out_channels; ++c) {
                    float sum = 0.0f;

                    for (int kh = 0; kh < kernel_height; ++kh) {
                        for (int kw = 0; kw < kernel_width; ++kw) {
                            for (int ic = 0; ic < in_channels; ++ic) {
                                int ih = h * strides[0] + kh ;
                                int iw = w * strides[1] + kw ;

                                if (padding == "same") {
                                    ih -= kernel_height / 2;
                                    iw -= kernel_width / 2;
                                }

                                if (ih >= 0 && ih < in_height && iw >= 0 && iw < in_width) {
                                    int input_idx = ((b * in_height + ih) * in_width + iw) * in_channels + ic;
                                    int kernel_idx = ((kh * kernel_width + kw) * in_channels + ic) * out_channels + c;

                                    sum += input[input_idx] * kernel[kernel_idx];
                                }
                            }
                        }
                    }

                    int output_idx = ((b * out_height + h) * out_width + w) * out_channels + c;
                    output[output_idx] =  sum + bias[c];
                }
            }
        }
    }

    std::cout << "Conv2D Output Size = " << output.size() << std::endl;

  
}