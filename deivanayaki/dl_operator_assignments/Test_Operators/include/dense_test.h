#ifndef DENSE_TEST_H
#define DENSE_TEST_H

#include <cassert>
#include <iostream>
#include <vector>
#include <fstream>
#include "../../extern/json.hpp"

using json = nlohmann::json;

class DenseTest{

public:

    static void checkDenseLayerOutput(const std::string& imagePath,const std::string& layerName,const std::vector<double>& feature_map);

};

#endif