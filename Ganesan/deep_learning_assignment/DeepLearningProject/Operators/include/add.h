#ifndef ADD_H
#define ADD_H

#include <vector>
#include <iostream>

class Add {
public:
    Add();
    std::vector<float> forward(const std::vector<float>& input1, const std::vector<float>& input2);
    ~Add();
};

#endif // ADD_H
