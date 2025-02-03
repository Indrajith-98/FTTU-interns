#ifndef FLATTEN_H
#define FLATTEN_H

#include <vector>

class Flatten {
public:
    // Function to flatten a 3D vector into a 1D vector
    std::vector<double> flatten(const std::vector<std::vector<std::vector<double>>>& input);
};

#endif // FLATTEN_H
