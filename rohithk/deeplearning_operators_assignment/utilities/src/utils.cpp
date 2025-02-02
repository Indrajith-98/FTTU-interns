#include <cmath>
#include <ctypes.h>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdio.h>
#include <utils.h>
using namespace std;
using json = nlohmann::json;

Utils::Utils() { cout << "Utils constructor" << endl; }
CImage Utils::deflattenTensor(CTensor &tensor) {

  int channels = tensor.shape[1];
  int width = tensor.shape[2];
  int height = tensor.shape[3];
  CImage deflattened_tensor(
      channels, vector<vector<double>>(width, vector<double>(height)));

  for (int c = 0; c < channels; c++) {
    for (int w = 0; w < width; w++) {
      for (int h = 0; h < height; h++) {
        deflattened_tensor[c][w][h] =
            tensor.data[c * width * height + w * height + h];
        ;
      }
    }
  }
  return deflattened_tensor;
}
CWeight Utils::deflattenTensorWithOutChannel(CTensor &tensor,
                                             int out_channels) {

  int channels = tensor.shape[1];
  int width = tensor.shape[2];
  int height = tensor.shape[3];

  CWeight deflattened_tensor(
      out_channels,
      vector<vector<vector<double>>>(
          channels, vector<vector<double>>(width, vector<double>(height))));
  for (int oc = 0; oc < out_channels; oc++) {
    for (int ic = 0; ic < channels; ic++) {
      for (int w = 0; w < width; w++) {
        for (int h = 0; h < height; h++) {
          int index = oc * channels * width * height + ic * width * height +
                      w * height + h;
          deflattened_tensor[oc][ic][w][h] = tensor.data[index];
        }
      }
    }
  }
  return deflattened_tensor;
}
void Utils::printCImage(const CImage &image) {
  for (size_t c = 0; c < image.size(); c++) {
    for (size_t w = 0; w < image[c].size(); w++) {
      cout << "(" << c << "," << w << ")" << endl;
      for (size_t h = 0; h < image[c][w].size(); h++) {
        cout << image[c][w][h] << " ";
      }
      cout << endl;
    }
    cout << endl;
  }
}
void Utils::printCImageReverse(const CImage &image) {
  for (size_t w = 0; w < image.size(); w++) {
    for (size_t h = 0; h < image[0].size(); h++) {
      cout << "(";
      for (size_t c = 0; c < image[0][0].size(); c++) {
        cout << image[w][h][c] << ",";
      }
      cout << ")";
    }
    cout << endl;
  }
}
void Utils::printKernel(const CImage &tensor) {
  int kernel_size = 2;
  int s = 0;
  for (int c = 0; c < 3; c++) {
    for (int r = 0; r < kernel_size; r++) {
      for (int w = 0; w < kernel_size; w++) {
        int start = -1;
        vector<vector<double>> temp1 = {};
        for (int s = 0; s < kernel_size; s++) {
          vector<double> temp = {};
          for (int k = 0; k < kernel_size; k++) {
            if ((k == 0 || r + s >= 2) && (start == -1)) {
              start = 1;
            } else {
              start = 0;
            }

            if ((k + w >= 2 && start == 1) ||
                ((s + r + kernel_size - 1 >= 3 && start == 1))) {
              break;
            }
            temp.push_back(tensor[c][s + r][k + w]);
          }
          temp1.push_back(temp);
        }
      }
    }
  }
}
double Utils::addElementsMatrix(const vector<vector<double>> &matrix) {
  double sum = 0;
  for (const auto &row : matrix) {
    for (double val : row) {
      sum += val;
    }
  }
  return sum;
}
double Utils::addElementsMatrix(const vector<vector<vector<double>>> &matrix) {
  double sum = 0;
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[0].size(); j++) {
      int temp = 0;
      for (int c = 0; c < matrix[0][0].size(); c++) {
        temp += matrix[i][j][c];
      }
      sum += temp;
    }
  }
  return sum;
}
vector<vector<double>>
Utils::multiplyMatrices(const vector<vector<vector<double>>> &A,
                        const vector<vector<vector<double>>> &B) {
  int rowsA = A.size();
  int colsA = A[0].size();
  int rowsB = B.size();
  int colsB = B[0].size();

  if (colsA != colsB && rowsA == rowsB) {
    throw invalid_argument("Matrix multiplication not possible: Columns of A "
                           "must match rows of B.");
  }

  vector<vector<double>> result(rowsA, vector<double>(colsB, 0));

  for (int i = 0; i < rowsA; i++) {
    for (int j = 0; j < colsB; j++) {
      double temp = 0;
      for (int c = 0; c < A[0][0].size(); c++) {
        temp += A[i][j][c] * B[i][j][c];
      }
      result[i][j] = temp;
    }
  }

  return result;
}
void Utils::printMatrix(const vector<vector<double>> &matrix) {
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}

vector<double> Utils::compute_mean(const CImage &image) {
  int C = image.size();
  int H = image[0].size();
  int W = image[0][0].size();

  vector<double> mean(C, 0.0f);

  for (int c = 0; c < C; ++c) {
    double sum = 0.0f;
    for (int h = 0; h < H; ++h) {
      for (int w = 0; w < W; ++w) {
        sum += image[c][h][w];
      }
    }
    mean[c] = sum / (H * W);
  }
  return mean;
}

vector<double> Utils::compute_variance(const CImage &image,
                                       const vector<double> &mean) {
  int C = image.size();
  int H = image[0].size();
  int W = image[0][0].size();

  vector<double> variance(C, 0.0f);

  for (int c = 0; c < C; ++c) {
    double sum = 0.0f;
    for (int h = 0; h < H; ++h) {
      for (int w = 0; w < W; ++w) {
        sum += pow(image[c][h][w] - mean[c], 2);
      }
    }
    variance[c] = sum / (H * W);
  }
  return variance;
}
vector<vector<vector<double>>>
Utils::unflattenImage(const vector<double> &flattened, int C, int H, int W) {
  vector<vector<vector<double>>> image(
      C, vector<vector<double>>(H, vector<double>(W, 0.0)));

  for (int c = 0; c < C; ++c) {
    for (int h = 0; h < H; ++h) {
      for (int w = 0; w < W; ++w) {
        image[c][h][w] = flattened[c * H * W + h * W + w];
      }
    }
  }

  return image;
}

vector<double> Utils::flattenImage(const CImage &image) {
  int C = image.size();
  int H = image[0].size();
  int W = image[0][0].size();

  vector<double> flattened(C * H * W, 0.0f);

  for (int c = 0; c < C; ++c) {
    for (int h = 0; h < H; ++h) {
      for (int w = 0; w < W; ++w) {
        flattened[c * H * W + h * W + w] = image[c][h][w];
      }
    }
  }
  return flattened;
}
json Utils::loadConfig(const string &config_file) {
  std::ifstream inputFile("../data.json");
  if (!inputFile) {
    std::cerr << "Error: Could not open file!" << std::endl;
    return 1;
  }
  json jsonData;
  inputFile >> jsonData;

  inputFile.close();
  return jsonData;
}
void Utils::loadBinaryFile(const std::string &filename) {
  std::ifstream file(filename, std::ios::binary | std::ios::ate);

  if (!file) {
    std::cerr << "Error: Cannot open file " << filename << std::endl;
    return;
  }

  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  std::vector<char> buffer(size);
  if (file.read(buffer.data(), size)) {
    std::cout << "Successfully loaded " << size << " bytes from " << filename
              << std::endl;
  } else {
    std::cerr << "Error: Failed to read the file." << std::endl;
  }

  file.close();
}
vector<double>
Utils::flatten4DVector(const vector<vector<vector<vector<double>>>> &tensor) {
  vector<double> flattened;

  for (const auto &out_channel : tensor) {       // Loop over output channels
    for (const auto &in_channel : out_channel) { // Loop over input channels
      for (const auto &row : in_channel) {       // Loop over width
        for (double val : row) {                 // Loop over height
          flattened.push_back(val);
        }
      }
    }
  }

  return flattened;
}