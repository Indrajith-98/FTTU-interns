#ifndef PReLU_H
#define PReLU_H

#include <vector>

class PReLU {
public:
    // Constructor to initialize alpha values
    PReLU(const std::vector<std::vector<std::vector<double>>>& alpha_values);

    // Apply PReLU activation to the feature map
    std::vector<std::vector<std::vector<double>>> applyPReLU(std::vector<std::vector<std::vector<double>>>& feature_map);

private:
    // 2D vector to store alpha values for each channel
    std::vector<std::vector<std::vector<double>>> alpha_values_; 
};

#endif // PReLU_H
