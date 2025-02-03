#ifndef CNN_FUNCTIONS_H
#define CNN_FUNCTIONS_H

#include "../Operators/include/conv.h"
#include "../Operators/include/max_pool.h"
#include "../Operators/include/flatten.h"
#include "../Operators/include/dense.h"
#include "../utilities/include/tensor_ops.h"
#include <iostream>

std::vector<std::vector<std::vector<double>>> performConvolution(const std::string& conv_layer_name, const std::vector<std::vector<std::vector<double>>>& input_feature_maps, TensorOps& tensor_ops);
std::vector<std::vector<std::vector<double>>> performMaxPooling(const std::string& pool_layer_name, const std::vector<std::vector<std::vector<double>>>& conv_feature_maps, TensorOps& tensor_ops);
std::vector<std::vector<std::vector<double>>> performConvolutionAndPooling(const std::string& conv_layer_name, const std::string& pool_layer_name, const std::vector<std::vector<std::vector<double>>>& input_feature_maps, TensorOps& tensor_ops);
std::vector<double> performFlattening(const std::vector<std::vector<std::vector<double>>>& input_feature_maps);
std::vector<double> performDense(const std::string& dense_layer_name, const std::vector<double>& input,std::string& activation, TensorOps& tensor_ops);
int predictNumber(const std::vector<double>& dense_output_1);

#endif // CNN_FUNCTIONS_H