#include <cmath>
#include <ctypes.h>
#include <stdio.h>
#include <utils.h>
using namespace std;

Utils::Utils() { cout << "Utils constructor" << endl; }
CImage Utils::deflattenTensor(CTensor &tensor) {

  int channels = tensor.shape[1];
  int width = tensor.shape[2];
  int height = tensor.shape[3];

  CImage deflattened_tensor(
      channels, vector<vector<float>>(width, vector<float>(height)));

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
void Utils::printCImage(const CImage &image) {
  for (size_t c = 0; c < image.size(); c++) {
    for (size_t w = 0; w < image[c].size(); w++) {
      for (size_t h = 0; h < image[c][w].size(); h++) {
        cout << image[c][w][h] << " ";
      }
      cout << endl;
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
        vector<vector<float>> temp1 = {};
        for (int s = 0; s < kernel_size; s++) {
          vector<float> temp = {};
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
        printMatrix(temp1);
      }
    }
  }
}

vector<vector<int>> Utils::multiplyMatrices(const vector<vector<int>> &A,
                                            const vector<vector<int>> &B) {
  int rowsA = A.size();
  int colsA = A[0].size();
  int rowsB = B.size();
  int colsB = B[0].size();

  if (colsA != rowsB) {
    throw invalid_argument("Matrix multiplication not possible: Columns of A "
                           "must match rows of B.");
  }

  vector<vector<int>> result(rowsA, vector<int>(colsB, 0));

  for (int i = 0; i < rowsA; i++) {
    for (int j = 0; j < colsB; j++) {
      for (int k = 0; k < colsA; k++) {
        result[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  return result;
}
float Utils::addElementsMatrix(const vector<vector<float>> &matrix) {
  float sum = 0;
  for (const auto &row : matrix) {
    for (float val : row) {
      sum += val;
    }
  }
  return sum;
}
vector<vector<float>> Utils::multiplyMatrices(const vector<vector<float>> &A,
                                              const vector<vector<float>> &B) {
  int rowsA = A.size();
  int colsA = A[0].size();
  int rowsB = B.size();
  int colsB = B[0].size();

  if (colsA != colsB && rowsA == rowsB) {
    throw invalid_argument("Matrix multiplication not possible: Columns of A "
                           "must match rows of B.");
  }

  vector<vector<float>> result(rowsA, vector<float>(colsB, 0));

  for (int i = 0; i < rowsA; i++) {
    for (int j = 0; j < colsB; j++) {
      result[i][j] = A[i][j] * B[i][j];
    }
  }
  return result;
}
void Utils::printMatrix(const vector<vector<int>> &matrix) {
  for (const auto &row : matrix) {
    for (int val : row) {
      cout << val << " ";
    }
    cout << "\n";
  }
}
void Utils::printMatrix(const vector<vector<float>> &matrix) {
  for (const auto &row : matrix) {
    for (int val : row) {
      cout << val << " ";
    }
    cout << "\n";
  }
}
vector<float> Utils::compute_mean(const CImage &image) {
  int C = image.size();
  int H = image[0].size();
  int W = image[0][0].size();

  vector<float> mean(C, 0.0f);

  for (int c = 0; c < C; ++c) {
    float sum = 0.0f;
    for (int h = 0; h < H; ++h) {
      for (int w = 0; w < W; ++w) {
        sum += image[c][h][w];
      }
    }
    mean[c] = sum / (H * W);
  }
  return mean;
}

vector<float> Utils::compute_variance(const CImage &image,
                                      const vector<float> &mean) {
  int C = image.size();
  int H = image[0].size();
  int W = image[0][0].size();

  vector<float> variance(C, 0.0f);

  for (int c = 0; c < C; ++c) {
    float sum = 0.0f;
    for (int h = 0; h < H; ++h) {
      for (int w = 0; w < W; ++w) {
        sum += pow(image[c][h][w] - mean[c], 2);
      }
    }
    variance[c] = sum / (H * W);
  }
  return variance;
}

// Function to apply batch normalization