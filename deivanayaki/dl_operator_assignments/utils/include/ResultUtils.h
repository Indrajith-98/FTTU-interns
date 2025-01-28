#ifndef RESULT_UTILS_H
#define RESULT_UTILS_H

#include <string>
#include <vector>
#include "../../extern/json.hpp"
#include <fstream>
#include <iostream>
#include <variant>

using json = nlohmann::json;

class ResultUtils {
public:
    static void appendPrediction(const std::string& imagePath, const std::vector<double>& probabilities,const std::map<std::string,std::vector<std::vector<std::vector<double>>>>& layer3d_outputs,const std::map<std::string,std::vector<double>>& layer1d_outputs);
    static void modelTest(const std::string& imagePath, const std::string& predicted);

};
#endif // RESULT_UTILS_H
