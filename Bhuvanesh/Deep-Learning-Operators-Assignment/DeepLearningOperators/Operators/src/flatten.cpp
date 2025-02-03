#include "flatten.h"

void flatten(const std::vector<float>& input, std::vector<float>& output,
             const std::array<int, 4>& input_shape, const std::array<int, 1>& output_shape) {
    int batch = input_shape[0];
    int in_height = input_shape[1], in_width = input_shape[2], in_channels = input_shape[3];

    assert(input.size() == batch * in_height * in_width * in_channels);
    assert(output.size() == batch * in_height * in_width * in_channels);

    std::cout << "Performing Flatten operation" << std::endl;

    for (int b = 0; b < batch; ++b) {
        int output_idx = b * in_height * in_width * in_channels;
        for (int h = 0; h < in_height; ++h) {
            for (int w = 0; w < in_width; ++w) {
                for (int c = 0; c < in_channels; ++c) {
                    int input_idx = ((b * in_height + h) * in_width + w) * in_channels + c;
                    output[output_idx++] = input[input_idx];
                }
            }
        }
    }
}
