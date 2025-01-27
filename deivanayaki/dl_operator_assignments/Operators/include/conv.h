#ifndef CONV_H
#define CONV_H

#include <iostream>
#include <vector>
#include <string>

class ConvLayer {
public:
    int filters;
    std::vector<int> input_shape;
    std::vector<int> output_shape;
    std::vector<int> kernel_size;
    std::vector<int> strides;
    std::string padding;
    std::vector<int> weights_shape;
    std::vector<double> weights;
    std::vector<double> biases;

    // Set attributes using the extracted values
    void setAttributes(int filters, const std::vector<int>& input_shape, const std::vector<int>& output_shape, 
                       const std::vector<int>& kernel_size, const std::vector<int>& strides, const std::string& padding, 
                       const std::vector<int>& weights_shape, const std::vector<double>& weights, const std::vector<double>& biases);

    // Print CNN layer attributes
    void printCNNattribute() const;
    std::vector<std::vector<std::vector<double>>> convolve(const std::vector<std::vector<std::vector<double>>>& input) const;
};

#endif
