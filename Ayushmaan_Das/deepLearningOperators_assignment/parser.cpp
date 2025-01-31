#include "onnx_model.h" // Include the correct header file
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstring>
#include "base64.h"

using json = nlohmann::json;

// Function Definitions
bool ONNXModel::loadModel(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error: Cannot open file " << filePath << std::endl;
        return false;
    }

    json modelJson;
    try
    {
        file >> modelJson;
    }
    catch (const json::parse_error &e)
    {
        std::cerr << "JSON Parsing Error: " << e.what() << std::endl;
        return false;
    }
    file.close();

    try
    {
        parseGraph(modelJson.at("graph"));
    }
    catch (const json::exception &e)
    {
        std::cerr << "Error accessing 'graph': " << e.what() << std::endl;
        return false;
    }

    return true;
}

void ONNXModel::parseGraph(const json &graph)
{
    try
    {
        std::cout << "Parsing graph..." << std::endl;
        for (const auto &initJson : graph.at("initializer"))
        {
            Tensor tensor;
            std::string tensorName = initJson.at("name").get<std::string>();

            if (initJson.contains("dims"))
            {
                if (initJson["dims"].is_array())
                {
                    for (const auto &dim : initJson["dims"])
                    {
                        if (dim.is_string())
                        {
                            tensor.shape.push_back(std::stoi(dim.get<std::string>()));
                        }
                        else if (dim.is_number())
                        {
                            tensor.shape.push_back(dim.get<int>());
                        }
                    }
                }
            }

            if (initJson.contains("rawData"))
            {
                std::string rawDataBase64 = initJson["rawData"].get<std::string>();
                std::vector<float> decodedData = decodeBase64RawData(rawDataBase64);
                tensor.data = decodedData;
            }

            tensors[tensorName] = tensor;
        }

        for (const auto &nodeJson : graph.at("node"))
        {
            Node node;
            node.name = nodeJson.at("name").get<std::string>();
            node.opType = nodeJson.at("opType").get<std::string>();
            node.inputs = nodeJson.at("input").get<std::vector<std::string>>();
            node.outputs = nodeJson.at("output").get<std::vector<std::string>>();
            nodes.push_back(node);
        }
    }
    catch (const json::exception &e)
    {
        std::cerr << "Error parsing graph: " << e.what() << std::endl;
    }
}

std::vector<float> ONNXModel::decodeBase64RawData(const std::string &rawDataBase64)
{
    std::vector<float> data;
    std::string decodedBytes = base64_decode(rawDataBase64);
    size_t numFloats = decodedBytes.size() / sizeof(float);
    data.resize(numFloats);
    std::memcpy(data.data(), decodedBytes.data(), decodedBytes.size());
    return data;
}
