#ifndef CONV_TEST_H
#define CONV_TEST_H

#include <cassert>
#include <iostream>
#include <vector>
#include <fstream>
#include "../../extern/json.hpp"

using json = nlohmann::json;

class ConvTest{

public:

    static void checkOutputShape(const std::vector<int>& expected_output_shape,int calculated_height, int calculated_width, int calculated_depth);
    static void checkConvLayerOutput(const std::string& imagePath,const std::string& layerName,const std::vector<std::vector<std::vector<double>>>& feature_map);

};

#endif