#ifndef SOFTMAX_H
#define SOFTMAX_H

#include <vector>
#include <string>

class Softmax {
public:
    void forward(const std::string& inputPath, const std::string& outputPath);
};

#endif // SOFTMAX_H
