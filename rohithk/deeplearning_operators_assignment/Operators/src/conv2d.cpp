#include <conv2d.h>
#include <iostream>
#include <utils.h>
using namespace std;

Conv2D::Conv2D(int in_channels, int out_channels, int kernel_size) {
  this->in_channels = in_channels;
  this->out_channels = out_channels;
  this->kernel_size = kernel_size;
  this->stride = 1;
  this->padding = 0;
  this->weights = CTensor();
  this->biases = CTensor();
}

Conv2D::Conv2D(int in_channels, int out_channels, int kernel_size, int stride,
               int padding, CTensor weights, CTensor biases) {
  this->in_channels = in_channels;
  this->out_channels = out_channels;
  this->kernel_size = kernel_size;
  this->stride = stride;
  this->padding = padding;
  this->weights.data = weights.data;
  this->weights.shape = weights.shape;
  this->biases.shape = biases.shape;
  this->biases.data = biases.data;
};
Conv2D::Conv2D(int in_channels, int out_channels, int kernel_size, int stride,
               int padding) {
  this->in_channels = in_channels;
  this->out_channels = out_channels;
  this->kernel_size = kernel_size;
  this->stride = stride;
  this->padding = padding;
  this->weights = CTensor();
  this->biases = CTensor();
};

CTensor Conv2D::addPadding(CTensor input) {
  int batch = input.shape[0];
  int in_channel = input.shape[1];
  int in_height = input.shape[2];
  int in_width = input.shape[3];

  int padding = this->padding;
  CTensor padded_input = input;
  return input;
};

CTensor Conv2D::performConvOp(CTensor input) {
  int batch = input.shape[0];
  int in_channel = input.shape[1];
  int in_height = input.shape[2];
  int in_width = input.shape[3];

  int out_channel = weights.shape[0];
  int kernel_size = weights.shape[2];
  int stride = this->stride;
  int padding = this->padding;

  int out_height = (in_height + 2 * padding - kernel_size) / stride + 1;
  int out_width = (in_width + 2 * padding - kernel_size) / stride + 1;
  cout << "Out Height : " << out_height << endl;
  CTensor output;
  std::vector<std::vector<float>> output2(out_width,
                                          std::vector<float>(out_height, 0.0));
  Utils::printMatrix(output2);
  CImage input_image = Utils::deflattenTensor(input);
  CImage weightsDeflattened = Utils::deflattenTensor(weights);
  int out_i = 0;
  int out_j = 0;
  for (int oc = 0; oc < this->out_channels; oc++) {
    int s = 0;
    for (int c = 0; c < in_channels; c++) {
      for (int r = 0; r < kernel_size; r += this->stride) {
        for (int w = 0; w < kernel_size; w += this->stride) {
          int start = -1;
          vector<vector<float>> pixelMatrix = {};
          for (int s = 0; s < kernel_size; s++) {
            vector<float> temp = {};
            for (int k = 0; k < kernel_size; k++) {
              if ((k == 0 || r + s >= in_height - 1) && (start == -1)) {
                start = 1;
              } else {
                start = 0;
              }

              if ((k + w >= in_height - 1 && start == 1) ||
                  ((s + r + kernel_size - 1 >= in_height && start == 1))) {
                break;
              }
              temp.push_back(input_image[c][s + r][k + w]);
            }
            pixelMatrix.push_back(temp);
          }
          vector<vector<float>> output =
              Utils::multiplyMatrices(pixelMatrix, weightsDeflattened[c]);
          output2[out_i][out_j] += Utils::addElementsMatrix(output);

          if (out_j < out_width - 1) {
            out_j++;
          } else {

            out_j = 0;
            out_i++;
            if (out_i >= out_height) {
              out_i = 0;
            }
          }
        }
      }
    }
  }
  Utils::printMatrix(output2);

  return output;
};
