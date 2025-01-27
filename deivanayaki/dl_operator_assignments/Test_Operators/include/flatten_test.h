#ifndef FLATTEN_TEST_H
#define FLATTEN_TEST_H

#include <cassert>
#include <iostream>
#include <vector>
#include <fstream>
#include "../../extern/json.hpp"

using json = nlohmann::json;

class FlattenTest{

public:

    static void checkFlattenOutput(const std::string& imagePath,const std::string& layerName,const std::vector<double>& feature_map);

};

#endif