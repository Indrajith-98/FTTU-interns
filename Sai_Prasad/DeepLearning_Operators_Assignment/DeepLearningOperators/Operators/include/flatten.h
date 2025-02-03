#ifndef FLATTEN_H
#define FLATTEN_H

#include <vector>
#include <array>
#include<cassert>
#include<iostream>

void flatten(const std::vector<float>& input, std::vector<float>& output,
             const std::array<int, 4>& input_shape, const std::array<int, 1>& output_shape);

#endif
