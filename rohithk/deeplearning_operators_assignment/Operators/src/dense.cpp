#include "dense.h"
#include <algorithm>
#include <array>
#include <chrono> // For timing
#include <cmath>
#include <fstream> // For file handling
#include <iostream>
#include <stdexcept>

void softmax(std::vector<float> &tensor) {
  float max_val = *std::max_element(tensor.begin(), tensor.end());
  float sum = 0.0f;
  for (auto &value : tensor) {
    value = std::exp(value - max_val);
    sum += value;
  }
  for (auto &value : tensor) {
    value /= sum;
  }
}

void dense(const std::vector<float> &input, const std::vector<float> &weights,
           const std::vector<float> &bias, std::vector<float> &output,
           const std::array<int, 2> &input_shape,
           const std::array<int, 2> &output_shape,
           const std::string &activation, std::string layername) {

  int input_size = input_shape[1];
  int output_size = output_shape[1];

  output.resize(output_size, 0.0f);

  if (weights.size() != input_size * output_size) {
    throw std::runtime_error(
        "Weights size does not match input_size * output_size.");
  }

  if (bias.size() != output_size) {
    throw std::runtime_error("Bias size does not match output_size.");
  }

  auto start_time = std::chrono::high_resolution_clock::now();

  for (int o = 0; o < output_size; ++o) {
    float sum = 0.0f;
    for (int i = 0; i < input_size; ++i) {
      sum += input[i] * weights[i * output_size + o];
    }
    output[o] = sum + bias[o];
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> execution_time = end_time - start_time;

  if (activation == "softmax") {
    softmax(output);
  }

  std::cout << "Dense Output Shape: [" << output_size << "]" << std::endl;

  std::cout << "Dense Layer Execution Time: " << execution_time.count()
            << " seconds" << std::endl;

  std::ofstream outfile("../data/cpp_outputs/" + layername + ".txt");
  if (outfile.is_open()) {
    for (int i = 0; i < output_size; i++) {
      outfile << output[i] << " ";
    }
    outfile << "\n";
    outfile.close();
    std::cout << "Output of First channel saved to data/cpp_outputs/" +
                     layername + ".txt"
              << std::endl;
  } else {
    std::cerr << "Could not  open file for writing!" << std::endl;
  }
}
