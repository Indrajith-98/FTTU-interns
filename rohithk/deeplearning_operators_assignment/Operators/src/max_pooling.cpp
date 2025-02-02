#include <algorithm>
#include <cmath>
// #include <conv2d.h>
#include <max_pooling.h>
#include <stdio.h>
#include <utils.h>
#include <vector>

using namespace std;
CImage max_pooling(const CImage &image, int kernel_size, int stride,
                   int padding) {

  int in_channel = 3;
  // Conv2D conv2d = Conv2D(in_channel, in_channel, kernel_size, stride,
  // padding);
  int in_height = image.size();
  int in_width = image[0].size();
  cout << in_height << " " << in_width << " " << image[0][0].size() << endl;
  if (padding < 0) {
    throw invalid_argument("Padding cannot be negative");
  }
  if (stride < 0) {
    throw invalid_argument("Stride cannot be negative");
  }
  if (kernel_size < 0) {
    throw invalid_argument("Kernel size cannot be negative");
  }
  // if (padding > 0) {
  //   image = conv2d.addPadding(image);
  // }

  int out_height = (in_height + 2 * padding - kernel_size) / stride + 1;
  int out_width = (in_width + 2 * padding - kernel_size) / stride + 1;
  int out_channels = in_channel;
  CImage full_output = CImage();
  full_output.assign(
      out_height,
      vector<vector<double>>(out_width, vector<double>(out_channels, 0.0f)));
  int out_i = 0;
  int out_j = 0;
  int s = 0;
  for (int r = 0; r < in_height; r += stride) {
    for (int w = 0; w < in_width; w += stride) {
      int start = -1;
      vector<vector<vector<double>>> pixelMatrix = {};
      for (int s = 0; s < kernel_size; s++) {
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
          temp.push_back(image[s + r][k + w]);
        }
        pixelMatrix.push_back(temp);
        temp.clear();
      }
      vector<double> max_value;
      max_value = {1e-19, 1e-19, 1e-19};
      for (int i = 0; i < pixelMatrix.size(); i++) {
        for (int j = 0; j < pixelMatrix[0].size(); j++) {
          for (int ms = 0; ms < pixelMatrix[0][0].size(); ms++) {

            max_value[ms] = max((double)max_value[ms], pixelMatrix[i][j][ms]);
          }
        }
      }
      full_output[out_i][out_j] = max_value;
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
  return full_output;
}
