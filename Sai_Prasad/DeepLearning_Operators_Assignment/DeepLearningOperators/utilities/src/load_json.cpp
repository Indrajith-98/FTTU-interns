#include "load_json.h"
#include <fstream>
#include <iostream>

nlohmann::json load_json(const std::string& file_path) {
    std::ifstream config_file(file_path);
    if (!config_file) {
        std::cerr << "Error: Could not open JSON file at " << file_path << std::endl;
        return {};
    }
    
    nlohmann::json config;
    config_file >> config;
    return config;
}
