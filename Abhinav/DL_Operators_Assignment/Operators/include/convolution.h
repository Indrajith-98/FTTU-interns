#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

class Convolution {
public:
    Convolution(const nlohmann::json& layerConfig);
    void forward(const std::string& inputPath, const std::vector<std::string>& weightPaths, const std::string& outputPath);

private:
    int kernel_size;
    int stride;
    std::string padding;
};

#endif // CONVOLUTION_H
