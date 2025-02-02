#ifndef UTILS_H
#define UTILS_H

#include <ctensor.h>
#include <ctypes.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdio.h>
#include <string>
#include <utils.h>
#include <vector>
using namespace std;
using json = nlohmann::json;

class Utils {
public:
  Utils();
  static void printTensor(CTensor &tensor);
  static CImage deflattenTensor(CTensor &tensor);
  static CWeight deflattenTensorWithOutChannel(CTensor &tensor,
                                               int out_channels);
  static void printCImage(const CImage &image);
  static void printKernel(const CImage &image);
  static void printMatrix(const vector<vector<double>> &matrix);
  static double addElementsMatrix(const vector<vector<double>> &A);
  static double addElementsMatrix(const vector<vector<vector<double>>> &A);
  static void printCImageReverse(const CImage &image);
  static vector<vector<double>>
  multiplyMatrices(const vector<vector<vector<double>>> &A,
                   const vector<vector<vector<double>>> &B);
  static vector<double> compute_mean(const CImage &image);

  static vector<double> compute_variance(const CImage &image,
                                         const vector<double> &mean);
  static vector<double> flattenImage(const CImage &image);
  static json loadConfig(const string &config_file);
  static void loadBinaryFile(const std::string &filename);
  static vector<vector<vector<double>>>
  unflattenImage(const vector<double> &flattened, int C, int H, int W);

  static vector<double>
  flatten4DVector(const vector<vector<vector<vector<double>>>> &tensor);
};
#endif
