#include <batch_normalisation.h>
#include <iostream>
#include <utils.h>
using namespace std;
CImage batch_norm(const CImage &image, const vector<float> &gamma,
                  const vector<float> &beta, float epsilon) {

  int C = image.size();
  int H = image[0].size();
  int W = image[0][0].size();

  vector<float> mean = Utils::compute_mean(image);
  vector<float> variance = Utils::compute_variance(image, mean);

  CImage normalized(C, vector<vector<float>>(H, vector<float>(W, 0.0f)));

  for (int c = 0; c < C; ++c) {
    for (int h = 0; h < H; ++h) {
      for (int w = 0; w < W; ++w) {
        float x_norm = (image[c][h][w] - mean[c]) / sqrt(variance[c] + epsilon);
        normalized[c][h][w] = gamma[c] * x_norm + beta[c];
      }
    }
  }
  return normalized;
}