#ifndef FLATTEN_H
#define FLATTEN_H

#include <vector>
#include <string>

class Flatten {
public:
    Flatten();
    void forward(const std::string& inputPath, const std::string& outputPath);

private:
    std::vector<float> flattenData(const std::vector<std::vector<std::vector<float>>>& input);
};

#endif
