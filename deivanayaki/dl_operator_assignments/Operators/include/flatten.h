#ifndef FLATTEN_H
#define FLATTEN_H

#include <vector>

class Flatten {
public:
    // Flatten the 3D feature map (height, width, channels) into a 1D vector
    std::vector<double> flatten(const std::vector<std::vector<std::vector<double>>>& input_map);

};

#endif
