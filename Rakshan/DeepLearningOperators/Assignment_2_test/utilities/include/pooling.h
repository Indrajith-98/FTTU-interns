// #ifndef POOLING_H
// #define POOLING_H

// #include <vector>

// void maxPooling(const std::vector<float> &input, std::vector<float> &output,
//                 int inputWidth, int inputHeight, int channels, int poolSize, int stride);

// #endif

#ifndef POOLING_H
#define POOLING_H

#include <vector>
#include <array>
#include <string>

void maxpooling(const std::vector<float>& input, std::vector<float>& output,
                   const std::array<int, 4>& input_shape, const std::array<int, 4>& output_shape,
                   const std::array<int, 2>& pool_size, const std::array<int, 2>& strides,
                   const std::string& padding, const std::string& layer_name);

#endif // MAX_POOLING2D_H