#ifndef TENSOR_OPS_H
#define TENSOR_OPS_H

#include <nlohmann/json.hpp>
#include <vector>
#include <string>

class TensorOps {
public:
    TensorOps(const nlohmann::json& jsonData);

    std::vector<std::vector<std::vector<double>>> getWeights(nlohmann::json layer, int filterIndex) const;
    double getBias(nlohmann::json layer, int filterIndex) const;
    nlohmann::json getLayer(std::string layerName) const;
    std::vector<std::vector<double>> getDenseWeights(nlohmann::json layer) const;
    std::vector<double> getDenseBias(nlohmann::json layer) const;
private:
    nlohmann::json data;
};

#endif // TENSOR_OPS_H
