#include "tensor_ops.h"
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
TensorOps::TensorOps(const nlohmann::json& jsonData) : data(jsonData) {}

std::vector<std::vector<std::vector<double>>> TensorOps::getWeights(nlohmann::json layer, int filterIndex) const {
    std::vector<std::vector<std::vector<double>>> filterWeights;
    auto weights = layer["weights"].get<std::vector<std::vector<std::vector<std::vector<double>>>>>();
    size_t weight_height = weights.size();
    size_t weight_width = weights[0].size();
    size_t weight_depth = weights[0][0].size();

    for (size_t k = 0; k < weight_depth; ++k) {
        std::vector<std::vector<double>> depthWeights;
        for (size_t j = 0; j < weight_height; ++j) {
            std::vector<double> widthWeights;
            for (size_t i = 0; i < weight_width; ++i) {
                widthWeights.push_back(weights[j][i][k][filterIndex]);
            }
            depthWeights.push_back(widthWeights);
        }
        filterWeights.push_back(depthWeights);
    }
    return filterWeights;
}

double TensorOps::getBias(nlohmann::json layer, int filterIndex) const {
    return layer["biases"][filterIndex].get<double>();
}
nlohmann::json TensorOps::getLayer(std::string layerName) const {
    for (const auto& layer : data["layers"]) {
        if (layer["name"] == layerName) {
            return layer;
        }
    }   
    return nullptr;
}

 std::vector<std::vector<double>> TensorOps::getDenseWeights(nlohmann::json layer) const{
    return layer["weights"].get<std::vector<std::vector<double>>>();
 }

 std::vector<double> TensorOps::getDenseBias(nlohmann::json layer) const{
    return layer["biases"].get<std::vector<double>>();
 }
