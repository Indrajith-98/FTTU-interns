#include "maxpool.h"
#include <algorithm>

void maxpool(const std::vector<float>& input_data, std::vector<float>& output_data, 
             int input_height, int input_width, int kernel_size, int stride) {
    
    int output_height = (input_height - kernel_size) / stride + 1;
    int output_width = (input_width - kernel_size) / stride + 1;
    output_data.resize(output_height * output_width);
    
    for (int h = 0; h < output_height; ++h) {
        for (int w = 0; w < output_width; ++w) {
            float max_val = -1e9;  // Very small number

            for (int kh = 0; kh < kernel_size; ++kh) {
                for (int kw = 0; kw < kernel_size; ++kw) {
                    int in_h = h * stride + kh;
                    int in_w = w * stride + kw;
                    int index = in_h * input_width + in_w;
                    max_val = std::max(max_val, input_data[index]);
                }
            }
            output_data[h * output_width + w] = max_val;
        }
    }
}
