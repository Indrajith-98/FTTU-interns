#ifndef INTERMEDIATE_RESULT_UTILS_H
#define INTERMEDIATE_RESULT_UTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "../../extern/json.hpp"

using json = nlohmann::json;

class IntermediateResultUtils {
public:
    static void storeIntermediateResults(
        const std::string& image_path, 
        const std::vector<double>& class_probabilities, 
        int predicted_index, 
        const std::string& predicted_label,
        const std::map<std::string,std::vector<std::vector<std::vector<double>>>>& layer3d_outputs,const std::map<std::string,std::vector<double>>& layer1d_outputs    );
};

#endif // INTERMEDIATE_RESULT_UTILS_H
