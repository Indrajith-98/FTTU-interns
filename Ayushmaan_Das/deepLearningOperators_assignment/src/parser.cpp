#include "onnx_model.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstring>
#include "base64.h"
#include <cstdint>

using json = nlohmann::json;

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

        std::string tensorName = "inputs";
        Tensor tensor;
        tensor.shape = {1, 28, 28};

        tensor.data.resize(28 * 28);
        for (size_t i = 0; i < 28 * 28; ++i)
        {
            tensor.data[i] = static_cast<float>(rand() % 256) / 255.0f;
        }

        tensors[tensorName] = tensor;
        std::cout << "Manually inserted input tensor: " << tensorName << " | Shape: 1x28x28" << std::endl;

        std::cout << "\n--- Checking loaded input tensors ---\n";
        for (const auto &tensor : tensors)
        {
            std::cout << "Tensor: " << tensor.first << " | Shape: ";
            for (int dim : tensor.second.shape)
                std::cout << dim << " ";
            std::cout << " | Data size: " << tensor.second.data.size() << std::endl;
        }
        std::cout << "--------------------------------------\n";

        for (const auto &initJson : graph.at("initializer"))
        {
            Tensor tensor;
            std::string tensorName = initJson.at("name").get<std::string>();
            std::cout << "Processing initializer: " << tensorName << std::endl;

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
                tensor.data = decodeBase64RawData(rawDataBase64);
            }
            tensors[tensorName] = tensor;
        }

        std::cout << "\n--- Checking loaded initializer tensors ---\n";
        for (const auto &tensor : tensors)
        {
            std::cout << "Tensor: " << tensor.first << " | Shape: ";
            for (int dim : tensor.second.shape)
                std::cout << dim << " ";
            std::cout << " | Data size: " << tensor.second.data.size() << std::endl;
        }
        std::cout << "--------------------------------------\n";

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
    std::vector<int64_t> intData;
    std::string decodedBytes = base64_decode(rawDataBase64);
    size_t numInts = decodedBytes.size() / sizeof(int64_t);
    intData.resize(numInts);
    std::memcpy(intData.data(), decodedBytes.data(), decodedBytes.size());

    std::vector<float> floatData(numInts);
    for (size_t i = 0; i < numInts; ++i)
    {
        floatData[i] = static_cast<float>(intData[i]);
    }

    return floatData;
}
