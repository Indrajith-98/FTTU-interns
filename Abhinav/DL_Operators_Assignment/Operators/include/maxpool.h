#ifndef MAXPOOL_H
#define MAXPOOL_H

#include <vector>
#include <string>

class MaxPooling2D {
public:
    MaxPooling2D(int pool_size);
    void forward(const std::string& inputPath, const std::string& outputPath);

private:
    int poolSize;
    std::vector<std::vector<float>> applyPooling(const std::vector<std::vector<float>>& input);
};

#endif
