#include "max_pooling2d.h"
#include <limits>
#include <algorithm> 
#include <iostream>

void max_pooling2d(const std::vector<float>& input, std::vector<float>& output,
                   const std::array<int, 4>& input_shape, const std::array<int, 4>& output_shape,
                   const std::array<int, 2>& pool_size, const std::array<int, 2>& strides,
                   const std::string& padding, const std::string& layer_name) {
    int batch = input_shape[0];
    int in_height = input_shape[1], in_width = input_shape[2], in_channels = input_shape[3];
    int out_height = output_shape[1], out_width = output_shape[2], out_channels = output_shape[3];
    int pool_height = pool_size[0], pool_width = pool_size[1];

    assert(input.size() == batch * in_height * in_width * in_channels);
    assert(output.size() == batch * out_height * out_width * out_channels);

    std::cout << "Performing MaxPooling operation for layer: " << layer_name << std::endl;

    for (int b = 0; b < batch; ++b) {
        for (int h = 0; h < out_height; ++h) {
            for (int w = 0; w < out_width; ++w) {
                for (int c = 0; c < out_channels; ++c) {
                    float max_val = -std::numeric_limits<float>::infinity();
                    for (int ph = 0; ph < pool_height; ++ph) {
                        for (int pw = 0; pw < pool_width; ++pw) {
                            int ih = h * strides[0] + ph;
                            int iw = w * strides[1] + pw;
                            if (padding == "same") {
                                ih -= pool_height / 2;
                                iw -= pool_width / 2;
                            }
                            if (ih >= 0 && ih < in_height && iw >= 0 && iw < in_width) {
                                int input_idx = ((b * in_height + ih) * in_width + iw) * in_channels + c;
                                max_val = std::max(max_val, input[input_idx]);
                            }
                        }
                    }
                    int output_idx = ((b * out_height + h) * out_width + w) * out_channels + c;
                    output[output_idx] = max_val;
                }
            }
        }
    }
}
