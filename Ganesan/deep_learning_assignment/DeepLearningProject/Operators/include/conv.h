#ifndef CONV_H
#define CONV_H

#include <vector>

// Function declaration for convolution
void conv(const std::vector<float>& input, const std::vector<float>& weights,
          std::vector<float>& output, int input_size, int stride, int padding, int kernel_size);

#endif  // CONV_H
