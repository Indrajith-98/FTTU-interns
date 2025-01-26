#ifndef BATCH_NORM_H
#define BATCH_NORM_H

#include <vector>
#include <iostream>

class BatchNorm {
public:
    // Constructor to initialize parameters
    BatchNorm(
        const std::vector<double>& gamma,
        const std::vector<double>& beta,
        const std::vector<double>& moving_mean,
        const std::vector<double>& moving_variance,
        float epsilon);

    // Method to apply batch normalization
    std::vector<std::vector<std::vector<double>>> applyBatchNorm(
        const std::vector<std::vector<std::vector<double>>>& feature_map);

    std::vector<double> applyBatchNorm(const std::vector<double>& dense_output);

private:
    std::vector<double> gamma_;
    std::vector<double> beta_;
    std::vector<double> moving_mean_;
    std::vector<double> moving_variance_;
    float epsilon_;
};

#endif // BATCH_NORM_H
