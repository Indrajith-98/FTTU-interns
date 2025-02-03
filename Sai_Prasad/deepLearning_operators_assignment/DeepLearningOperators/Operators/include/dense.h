#ifndef DENSE_H
#define DENSE_H

#include <vector>
#include <string>
#include <array>
#include<iostream>
#include<cassert>

void dense(const std::vector<float>& input, const std::vector<float>& weights,
           const std::vector<float>& bias, std::vector<float>& output,
           const std::array<int, 1>& input_shape, const std::array<int, 1>& output_shape,
           const std::string& activation, const std::string& layer_name);

#endif
