#ifndef PRELU_TEST_H
#define PRELU_TEST_H

#include <cassert>
#include <iostream>
#include <vector>
#include <fstream>
#include "../../extern/json.hpp"

using json = nlohmann::json;

class PReluTest{

public:

    static void checkPReluLayerOutput(const std::string& imagePath,const std::string& layerName,const std::vector<std::vector<std::vector<double>>>& feature_map);

};

#endif