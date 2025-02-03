#include "cnn_functions.h"

std::vector<std::vector<std::vector<double>>> performConvolution(const std::string& conv_layer_name, const std::vector<std::vector<std::vector<double>>>& input_feature_maps, TensorOps& tensor_ops) {
    std::vector<std::vector<std::vector<double>>> conv_feature_maps;
    nlohmann::json conv_layer = tensor_ops.getLayer(conv_layer_name);
    int conv_kernel_height = conv_layer["kernel_size"][0];
    int conv_kernel_width = conv_layer["kernel_size"][1];
    int input_image_height = conv_layer["input_shape"][1];
    int input_image_width = conv_layer["input_shape"][2];
    int input_image_depth = conv_layer["input_shape"][3];
    int conv_num_filters = conv_layer["filters"];

    Convolution conv = Convolution(conv_kernel_height, conv_kernel_width, input_image_depth);
    
    for(int filter_index = 0; filter_index < conv_num_filters; filter_index++){
        std::vector<std::vector<std::vector<double>>> conv_weights = tensor_ops.getWeights(conv_layer, filter_index);
        double conv_bias = tensor_ops.getBias(conv_layer, filter_index);
        std::vector<std::vector<double>> conv_output = conv.performConvolution(input_feature_maps, input_image_depth, input_image_height, input_image_width, conv_weights, conv_bias);
        conv_feature_maps.push_back(conv_output);
    }
    return conv_feature_maps;
}

std::vector<std::vector<std::vector<double>>> performMaxPooling(const std::string& pool_layer_name, const std::vector<std::vector<std::vector<double>>>& conv_feature_maps, TensorOps& tensor_ops) {
    nlohmann::json pool_layer = tensor_ops.getLayer(pool_layer_name);
    int pool_height = static_cast<int>(pool_layer["input_shape"][1]) / static_cast<int>(pool_layer["output_shape"][1]);
    int pool_width = static_cast<int>(pool_layer["input_shape"][2]) / static_cast<int>(pool_layer["output_shape"][2]);
    int conv_feature_maps_depth = conv_feature_maps.size();
    int conv_feature_maps_height = conv_feature_maps[0].size();
    int conv_feature_maps_width = conv_feature_maps[0][0].size();
    MaxPooling max_pool = MaxPooling(pool_height, pool_width);
    std::vector<std::vector<std::vector<double>>> max_pooled_feature_maps;
    max_pooled_feature_maps = max_pool.performMaxPooling(conv_feature_maps, conv_feature_maps_depth, conv_feature_maps_height, conv_feature_maps_width);
    return max_pooled_feature_maps;
}

std::vector<std::vector<std::vector<double>>> performConvolutionAndPooling(const std::string& conv_layer_name, const std::string& pool_layer_name, const std::vector<std::vector<std::vector<double>>>& input_feature_maps, TensorOps& tensor_ops) {
    std::vector<std::vector<std::vector<double>>> conv_feature_maps = performConvolution(conv_layer_name, input_feature_maps, tensor_ops);
    std::vector<std::vector<std::vector<double>>> max_pooled_feature_maps = performMaxPooling(pool_layer_name, conv_feature_maps, tensor_ops);
    return max_pooled_feature_maps;
}

std::vector<double> performFlattening(const std::vector<std::vector<std::vector<double>>>& input_feature_maps){
    Flatten flatten = Flatten();
    std::vector<double> flattened_output = flatten.flatten(input_feature_maps);
    return flattened_output;
}

std::vector<double> performDense(const std::string& dense_layer_name, const std::vector<double>& input, std::string& activation, TensorOps& tensor_ops){
    nlohmann::json dense_layer = tensor_ops.getLayer(dense_layer_name);
    std::vector<std::vector<double>> weights = tensor_ops.getDenseWeights(dense_layer);
    std::vector<double> bias = tensor_ops.getDenseBias(dense_layer);
    Dense dense = Dense(input, weights, bias, activation);
    std::vector<double> dense_output = dense.forward();
    return dense_output;
}

int predictNumber(const std::vector<double>& dense_output_1) {
    auto max_element_iter = std::max_element(dense_output_1.begin(), dense_output_1.end());
    int predicted_number = std::distance(dense_output_1.begin(), max_element_iter);
    return predicted_number;
}
