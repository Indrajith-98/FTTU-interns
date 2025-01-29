#ifndef CONV2D_H
#define CONV2D_H

#include "utils.h"
#include <vector>

class Conv2D {
public:
  int in_channels;
  int out_channels;
  int kernel_size;
  int stride;
  int padding;
  CTensor weights;
  CTensor biases;

  // Constructors
  Conv2D(int in_channels, int out_channels, int kernel_size);
  Conv2D(int in_channels, int out_channels, int kernel_size, int stride,
         int padding, CTensor weights, CTensor biases);
  Conv2D(int in_channels, int out_channels, int kernel_size, int stride,
         int padding);

  // Member functions
  CTensor addPadding(CTensor input);
  CTensor performConvOp(CTensor input);
  std::vector<CTensor> forward(const std::vector<CTensor> &inputs);
};

#endif // CONV2D_H