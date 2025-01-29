#ifndef UTILS_H
#define UTILS_H

#include <ctensor.h>
#include <ctypes.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Utils {
public:
  Utils();
  static void printTensor(CTensor &tensor);
  static CImage deflattenTensor(CTensor &tensor);
  static void printCImage(const CImage &image);
  static void printKernel(const CImage &image);
  static void printMatrix(const vector<vector<int>> &matrix);
  static void printMatrix(const vector<vector<float>> &matrix);
  static float addElementsMatrix(const vector<vector<float>> &A);
  static vector<vector<int>> multiplyMatrices(const vector<vector<int>> &A,
                                              const vector<vector<int>> &B);
  static vector<vector<float>> multiplyMatrices(const vector<vector<float>> &A,
                                                const vector<vector<float>> &B);
};
#endif
