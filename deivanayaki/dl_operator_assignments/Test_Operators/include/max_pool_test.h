#ifndef MAX_POOL_TEST_H
#define MAX_POOL_TEST_H

#include <cassert>
#include <iostream>
#include <vector>
#include <fstream>
#include "../../extern/json.hpp"

using json = nlohmann::json;

class MaxPoolTest{

public:

    static void checkMaxPoolLayerOutput(const std::string& imagePath,const std::string& layerName,const std::vector<std::vector<std::vector<double>>>& feature_map);

};

#endif