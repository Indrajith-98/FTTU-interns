#include <algorithm>
#include <cmath>
#include <max_pooling.h>
#include <vector>

using namespace std;
CImage max_pooling(
    const CImage& image, 
    int kernel_size, int stride, int padding
) {
    int C = image.size();  // Number of channels
    int H = image[0].size(); // Original height
    int W = image[0][0].size(); // Original width

    // Add padding to the image
    int padded_H = H + 2 * padding;
    int padded_W = W + 2 * padding;

    CImage padded_image(C, vector<vector<float>>(padded_H, vector<float>(padded_W, 0.0f)));

    // Copy original image into padded version
    for (int c = 0; c < C; ++c) {
        for (int h = 0; h < H; ++h) {
            for (int w = 0; w < W; ++w) {
                padded_image[c][h + padding][w + padding] = image[c][h][w];
            }
        }
    }

    // Compute output dimensions
    int new_H = (padded_H - kernel_size) / stride + 1;
    int new_W = (padded_W - kernel_size) / stride + 1;

    // Initialize output tensor
    CImage pooled(C, vector<vector<float>>(new_H, vector<float>(new_W, 0.0f)));

    // Apply max pooling
    for (int c = 0; c < C; ++c) {
        for (int h = 0; h < new_H; ++h) {
            for (int w = 0; w < new_W; ++w) {
                float max_val = -1e9; // Start with a very small number
                for (int kh = 0; kh < kernel_size; ++kh) {
                    for (int kw = 0; kw < kernel_size; ++kw) {
                        int h_idx = h * stride + kh;
                        int w_idx = w * stride + kw;
                        max_val = max(max_val, padded_image[c][h_idx][w_idx]);
                    }
                }
                pooled[c][h][w] = max_val;
            }
        }
    }

    return pooled;
}

// Main fun