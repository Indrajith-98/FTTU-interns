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
void transform3DVector(const vector<vector<vector<double>>> &full_output,
                       CImage &required) {
  int channels = 32;
  int width = 30;
  int height = 30;

  for (int c = 0; c < channels; c++) {
    for (int w = 0; w < width; w++) {
      for (int h = 0; h < height; h++) {
        required[c][w][h] = full_output[h][w][c];
      }
    }
  }
}
Conv2D::Conv2D(int in_channels, int out_channels, int kernel_size, int stride,
               int padding, CTensor weights, CTensor biases) {
  if (padding < 0) {
    throw invalid_argument("Padding cannot be negative");
  }
  if (stride < 0) {
    throw invalid_argument("Stride cannot be negative");
  }
  if (kernel_size < 0) {
    throw invalid_argument("Kernel size cannot be negative");
  }
  if (in_channels < 0) {
    throw invalid_argument("Input channels cannot be negative");
  }
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
  if (padding < 0) {
    throw invalid_argument("Padding cannot be negative");
  }
  if (stride < 0) {
    throw invalid_argument("Stride cannot be negative");
  }
  if (kernel_size < 0) {
    throw invalid_argument("Kernel size cannot be negative");
  }

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
  CImage temp = Utils::deflattenTensor(input);
  for (int p = 0; p < this->padding; p++) {
    for (int i = 0; i < in_channels; i++) {
      temp[i].insert(temp[i].begin(), std::vector<double>(in_width, 0));
      temp[i].insert(temp[i].end(), std::vector<double>(in_width, 0));
      for (int j = 0; j < in_height; j++) {
        temp[i][j].insert(temp[i][j].begin(), 0);
        temp[i][j].insert(temp[i][j].end(), 0);
      }
    }
  }
  CTensor output = CTensor();
  output.data = Utils::flattenImage(temp);
  output.shape = {batch, in_channel, in_height + 2, in_width + 2};
  return input;
};

CImage Conv2D::performConvOp(CTensor input) {
  int batch = input.shape[0];
  int in_channel = input.shape[1];
  int in_height = input.shape[2];
  int in_width = input.shape[3];

  int out_channel = weights.shape[0];
  int kernel_size = weights.shape[2];
  int stride = this->stride;
  int padding = this->padding;
  
  if (padding < 0) {
    throw invalid_argument("Padding cannot be negative");
  }
  if (stride < 0) {
    throw invalid_argument("Stride cannot be negative");
  }
  if (kernel_size < 0) {
    throw invalid_argument("Kernel size cannot be negative");
  }
  if (padding > 0) {
    input = addPadding(input);
  }

  int out_height = (in_height + 2 * padding - kernel_size) / stride + 1;
  int out_width = (in_width + 2 * padding - kernel_size) / stride + 1;

  CTensor temp = CTensor();
  temp.shape = {out_channel, out_height, out_width};
  CImage full_output = CImage();
  full_output.assign(
      out_channels,
      vector<vector<double>>(out_width, vector<double>(out_height, 0.0f)));

  std::vector<std::vector<double>> output2(
      out_width, std::vector<double>(out_height, 0.0));

  CImage input_image = Utils::unflattenImage(input.data, 32, 32, 3);
  CWeight weightsDeflattened =
      Utils::deflattenTensorWithOutChannel(weights, this->out_channels);

  int out_i = 0;
  int out_j = 0;
  for (int oc = 0; oc < this->out_channels; oc++) {
    int s = 0;
    for (int r = 0; r < in_height; r += this->stride) {
      for (int w = 0; w < in_width; w += this->stride) {
        int start = -1;
        vector<vector<vector<double>>> pixelMatrix = {};
        for (int s = 0; s < in_channel; s++) {
          vector<vector<double>> temp = {};
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
            temp.push_back(input_image[s + r][k + w]);
          }
          pixelMatrix.push_back(temp);
        }
        vector<vector<double>> output =
            Utils::multiplyMatrices(pixelMatrix, weightsDeflattened[oc]);

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
    full_output[oc] = output2;
    output2.assign(out_width, std::vector<double>(out_height, 0.0));
  }
  return full_output;
};