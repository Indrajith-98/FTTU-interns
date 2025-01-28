// #include "dense.h"
// #include <cmath>
// #include <algorithm>



// void dense(const std::vector<float> &input, const std::vector<float> &weights, const std::vector<float> &biases,
//            std::vector<float> &output, int inputSize, int outputSize)
// {
//     output.resize(outputSize, 0.0f);
//     for (int o = 0; o < outputSize; ++o)
//     {
//         for (int i = 0; i < inputSize; ++i)
//         {
//             output[o] += input[i] * weights[o * inputSize + i];
//         }
//         output[o] += biases[o];
//     }
// }

// void denseLayerWithSoftmax(const std::vector<float> &input, const std::vector<float> &weights,
//                            const std::vector<float> &biases, std::vector<float> &output,
//                            int inputSize, int outputSize)
// {
//     // Initialize the output vector
//     output.resize(outputSize, 0.0f);

//     // Perform the dense operation (matrix multiplication and bias addition)
//     for (int o = 0; o < outputSize; ++o)
//     {
//         for (int i = 0; i < inputSize; ++i)
//         {
//             output[o] += input[i] * weights[o * inputSize + i];
//         }
//         output[o] += biases[o];
//     }

//     // Apply softmax activation
//     float maxVal = *std::max_element(output.begin(), output.end());
//     float sumExp = 0.0f;

//     for (float &value : output)
//     {
//         value = std::exp(value - maxVal); // Subtract maxVal for numerical stability
//         sumExp += value;
//     }

//     for (float &value : output)
//     {
//         value /= sumExp;
//     }
// }
// // #include "dense.h"
// // #include <cmath>
// // #include <algorithm>
// // #include <stdexcept>
// // #include <iostream>

// // void dense(const std::vector<float> &input, const std::vector<float> &weights, const std::vector<float> &biases,
// //            std::vector<float> &output, int inputSize, int outputSize)
// // {
// //     if (input.size() != inputSize) {
// //         std::cerr << "Error: Input size mismatch. Expected: " << inputSize << ", Got: " << input.size() << std::endl;
// //         throw std::invalid_argument("Input size does not match expected size.");
// //     }
// //     if (weights.size() != inputSize * outputSize) {
// //         std::cerr << "Error: Weights size mismatch. Expected: " << (inputSize * outputSize) << ", Got: " << weights.size() << std::endl;
// //         throw std::invalid_argument("Weights size does not match expected size.");
// //     }
// //     if (biases.size() != 512) {
// //         std::cerr << "Error: Biases size mismatch. Expected: " << outputSize << ", Got: " << biases.size() << std::endl;
// //         throw std::invalid_argument("Biases size does not match expected size.");
// //     }

// //     output.assign(outputSize, 0.0f);

// //     for (int o = 0; o < 512; ++o) {
// //         for (int i = 0; i < 8192; ++i) {
// //             output[o] += input[i] * weights[o * inputSize + i];
// //         }
// //         output[o] += biases[o];
// //     }
// //     output.resize(outputSize, 0.0f);
// // //     for (int o = 0; o < outputSize; ++o)
// // //     {
// // //         for (int i = 0; i < inputSize; ++i)
// // //         {
// // //             output[o] += input[i] * weights[o * inputSize + i];
// // //         }
// // //         output[o] += biases[o];
// // //     }
// // }


// // void denseLayerWithSoftmax(const std::vector<float> &input, const std::vector<float> &weights,
// //                            const std::vector<float> &biases, std::vector<float> &output,
// //                            int inputSize, int outputSize)
// // {
// //     // Ensure input, weights, and biases have valid dimensions
// //     if (input.size() != inputSize)
// //         throw std::invalid_argument("Input size does not match expected size.");
// //     if (weights.size() != inputSize * outputSize)
// //         throw std::invalid_argument("Weights size does not match expected size.");
// //     if (biases.size() != outputSize)
// //         throw std::invalid_argument("Biases size does not match expected size.");

// //     // Initialize the output vector
// //     output.assign(outputSize, 0.0f);

// //     // Perform dense computation
// //     for (int o = 0; o < outputSize; ++o)
// //     {
// //         for (int i = 0; i < inputSize; ++i)
// //         {
// //             output[o] += input[i] * weights[o * inputSize + i];
// //         }
// //         output[o] += biases[o];
// //     }

// //     // Apply softmax activation
// //     float maxVal = *std::max_element(output.begin(), output.end());
// //     float sumExp = 0.0f;

// //     for (float &value : output)
// //     {
// //         value = std::exp(value - maxVal); // Subtract maxVal for numerical stability
// //         sumExp += value;
// //     }

// //     for (float &value : output)
// //     {
// //         value /= sumExp;
// //     }
// // }





#include "dense.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <iomanip>

void relu(std::vector<float>& tensor) {
    for (auto& value : tensor) {
        value = std::max(0.0f, value);
    }
}

void softmax(std::vector<float>& tensor) {
    float max_val = *std::max_element(tensor.begin(), tensor.end());
    float sum = 0.0f;
    for (auto& value : tensor) {
        value = std::exp(value - max_val);
        sum += value;
    }
    for (auto& value : tensor) {
        value /= sum;
    }
}

void dense(const std::vector<float>& input, const std::vector<float>& weights,
           const std::vector<float>& bias, std::vector<float>& output,
           const std::array<int, 2>& input_shape, const std::array<int, 2>& output_shape,
           const std::string& activation, const std::string layer_name) {
    int input_size = input_shape[1];
    int output_size = output_shape[1];

    for (int o = 0; o < output_size; ++o) {
        float sum = 0.0f;
        for (int i = 0; i < input_size; ++i) {
            sum += input[i] * weights[i * output_size + o];
        }
        output[o] = sum + bias[o];
    }

    if (activation == "relu") {
        relu(output);
    } else if (activation == "softmax") {
        softmax(output);
    }

    std::cout << "Dense Output Size = " << output.size() << std::endl;
}

