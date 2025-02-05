#ifndef MATMUL_H
#define MATMUL_H

#include <vector>

class MatMul {
public:
    std::vector<float> forward(const std::vector<float>& input, 
                               const std::vector<float>& weights, 
                               const std::vector<float>& bias, 
                               int input_size, int output_size);
};

#endif // MATMUL_H
