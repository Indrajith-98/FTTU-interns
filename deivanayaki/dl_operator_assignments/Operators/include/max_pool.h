#ifndef MAX_POOL_H
#define MAX_POOL_H

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits>

class MaxPool {
public:
    // Constructor
    MaxPool(std::vector<int> pool_size, std::vector<int> strides);

    // Apply max pooling on the input feature map
    std::vector<std::vector<std::vector<double>>> applyMaxPool(
        const std::vector<std::vector<std::vector<double>>>& input_map);

private:
    std::vector<int> pool_size;  // Pooling window size: {height, width}
    std::vector<int> strides;   // Strides: {stride_height, stride_width}


};

#endif 