#ifndef MAXPOOLING_H
#define MAXPOOLING_H

#include <vector>
#include <string>
#include <array>

// Updated function signature without the padding parameter.
void max_pooling2d(const std::vector<float>& input, std::vector<float>& output,
                const std::array<int, 4>& input_shape, const std::array<int, 4>& output_shape,
                const std::array<int, 2>& pool_size, const std::array<int, 2>& strides,
                const std::string& layer_name);

#endif
