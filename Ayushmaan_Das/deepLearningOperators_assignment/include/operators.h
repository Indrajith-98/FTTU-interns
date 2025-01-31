#ifndef OPERATORS_H
#define OPERATORS_H

#include <vector>
#include <iostream>
#include <cmath>
#include "onnx_model.h"

bool executeAdd(const Tensor &input1, const Tensor &input2, Tensor &output);
bool executeMul(const Tensor &input1, const Tensor &input2, Tensor &output);
bool executeRelu(const Tensor &input, Tensor &output);
bool executeMatMul(const Tensor &input1, const Tensor &input2, Tensor &output);
bool executeSoftmax(const Tensor &input, Tensor &output);
bool executeReshape(const Tensor &input, Tensor &output, const std::vector<int> &newShape);
bool executeMaxPool(const Tensor &input, Tensor &output, int kernelSize);
bool executeGlobalAveragePool(const Tensor &input, Tensor &output);

#endif
