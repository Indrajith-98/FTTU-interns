#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <vector>

class Activation {
public:
    
    static void relu(std::vector<std::vector<float>>& input);

    static void leaky_relu(std::vector<std::vector<float>>& input, float alpha = 0.01);
    
    static void sigmoid(std::vector<std::vector<float>>& input);

    static void tanh(std::vector<std::vector<float>>& input);

    static void softmax(std::vector<std::vector<float>>& input);
};

#endif 
