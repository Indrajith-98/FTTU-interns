#ifndef ONNX_MODEL_H
#define ONNX_MODEL_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <nlohmann/json.hpp>
#include "base64.h"

struct Tensor
{
    std::vector<int> shape;
    std::vector<float> data;
};

struct Node
{
    std::string name;
    std::string opType;
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;
};

class ONNXModel
{
public:
    std::unordered_map<std::string, Tensor> tensors;
    std::vector<Node> nodes;

    bool loadModel(const std::string &filePath);

private:
    void parseGraph(const nlohmann::json &graph);
    std::vector<float> decodeBase64RawData(const std::string &rawDataBase64);
};

#endif
