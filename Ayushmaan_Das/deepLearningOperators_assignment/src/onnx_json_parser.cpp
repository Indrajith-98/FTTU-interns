#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstring>
#include "base64.h"

using json = nlohmann::json;

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

    void log(const std::string &message)
    {
        std::cout << message << std::endl;
    }

    bool loadModel(const std::string &filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            log("Error: Cannot open file " + filePath);
            return false;
        }

        json modelJson;
        try
        {
            file >> modelJson;
        }
        catch (const json::parse_error &e)
        {
            log("JSON Parsing Error: " + std::string(e.what()));
            return false;
        }
        file.close();

        try
        {
            parseGraph(modelJson.at("graph"));
        }
        catch (const json::exception &e)
        {
            log("Error accessing 'graph': " + std::string(e.what()));
            return false;
        }

        return true;
    }

    void parseGraph(const json &graph)
    {
        try
        {
            log("Parsing graph...");
            for (const auto &initJson : graph.at("initializer"))
            {
                Tensor tensor;
                std::string tensorName = initJson.at("name").get<std::string>();
                log("Processing initializer: " + tensorName);

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
                    log("Decoding rawData for " + tensorName);
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
                log("Parsed node: " + node.name + " (" + node.opType + ")");
            }
        }
        catch (const json::exception &e)
        {
            log("Error parsing graph: " + std::string(e.what()));
        }
    }

    std::vector<float> decodeBase64RawData(const std::string &rawDataBase64)
    {
        std::vector<float> data;
        std::string decodedBytes = base64_decode(rawDataBase64);
        size_t numFloats = decodedBytes.size() / sizeof(float);
        data.resize(numFloats);
        std::memcpy(data.data(), decodedBytes.data(), decodedBytes.size());
        return data;
    }
};

int main()
{
    ONNXModel model;
    if (model.loadModel("../configs/model_config.json"))
    {
        model.log("Model successfully loaded.");
    }

    return 0;
}
