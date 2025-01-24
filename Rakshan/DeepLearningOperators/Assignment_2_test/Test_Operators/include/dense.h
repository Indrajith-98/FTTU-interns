// // utilities/include/dense.h
// #ifndef DENSE_H
// #define DENSE_H

// #include <vector>

// void dense(const std::vector<float> &input, const std::vector<float> &weights, const std::vector<float> &biases,
//            std::vector<float> &output, int inputSize, int outputSize);

// void denseLayerWithSoftmax(const std::vector<float> &input, const std::vector<float> &weights,
//                            const std::vector<float> &biases, std::vector<float> &output,
//                            int inputSize, int outputSize);

// #endif


#ifndef DENSE_H
#define DENSE_H    


#include <vector>
#include <array>
#include <string>

void dense(const std::vector<float>& input, const std::vector<float>& weights,
           const std::vector<float>& bias, std::vector<float>& output,
           const std::array<int, 2>& input_shape, const std::array<int, 2>& output_shape,
           const std::string& activation, const std::string layer_name);

#endif // DENSELAYER_H 
