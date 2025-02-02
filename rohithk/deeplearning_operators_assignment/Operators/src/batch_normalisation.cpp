#include <batch_normalisation.h>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utils.h>

using namespace std;

CImage batch_norm(const CImage &input, const vector<double> &gamma,
                  const vector<double> &beta, double epsilon) {
  // Validate input dimensions
  const int W = 32; // width
  const int H = 32; // height
  const int C = 3;  // channels (RGB)

  if (input.size() != W || input[0].size() != H || input[0][0].size() != C) {
    throw runtime_error("Input must be 32x32x3");
  }

  // Validate gamma and beta
  if (gamma.size() != C || beta.size() != C) {
    throw runtime_error("gamma and beta must have size 3 (one per channel)");
  }

  // Initialize output with same dimensions as input
  CImage normalized(W, vector<vector<double>>(H, vector<double>(C, 0.0)));

  // Calculate mean for each channel
  vector<double> mean(C, 0.0);
  for (int c = 0; c < C; ++c) {
    double sum = 0.0;
    for (int w = 0; w < W; ++w) {
      for (int h = 0; h < H; ++h) {
        sum += input[w][h][c];
      }
    }
    mean[c] = sum / (W * H);
  }

  // Calculate variance for each channel
  vector<double> variance(C, 0.0);
  for (int c = 0; c < C; ++c) {
    double sum_sq = 0.0;
    for (int w = 0; w < W; ++w) {
      for (int h = 0; h < H; ++h) {
        double diff = input[w][h][c] - mean[c];
        sum_sq += diff * diff;
      }
    }
    variance[c] = sum_sq / (W * H);
  }

  // Apply batch normalization
  for (int c = 0; c < C; ++c) {
    double std_dev = sqrt(variance[c] + epsilon);
    for (int w = 0; w < W; ++w) {
      for (int h = 0; h < H; ++h) {
        double normalized_value = (input[w][h][c] - mean[c]) / std_dev;
        normalized[w][h][c] = gamma[c] * normalized_value + beta[c];
      }
    }
  }

  return normalized;
}
