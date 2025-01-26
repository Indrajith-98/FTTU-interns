#ifndef BATCH_NORM_TEST_H
#define BATCH_NORM_TEST_H

#include <cassert>
#include <iostream>
#include <vector>
#include <fstream>
#include "../../extern/json.hpp"

using json = nlohmann::json;

class BatchNormTest{

public:

    static void checkBatchNormLayerOutput(const std::string& imagePath,const std::string& layerName,const std::vector<std::vector<std::vector<double>>>& feature_map);

    static void checkBatchNormLayerOutput(const std::string& imagePath,const std::string& layerName,const std::vector<double>& feature_map);

};

#endif