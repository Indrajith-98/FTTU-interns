#ifndef DENSE_H
#define DENSE_H

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

class Dense {
public:
    Dense(const nlohmann::json& layerConfig);
    void forward(const std::string& inputPath, const std::vector<std::string>& weightPaths, const std::string& outputPath);

private:
    int input_size;
    int output_size;
};

#endif // DENSE_H
