#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <vector>
#include "../../extern/json.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

using json = nlohmann::json;

class FileUtils {
public:
    static std::vector<std::vector<std::vector<double>>> read_image_matrix(const std::string& file_path);

    static void display_image_shape(const std::vector<std::vector<std::vector<double>>>& image_matrix);

    static json read_model_config(const std::string& file_path);

    static std::string extractFilename(const std::string& filePath);
};

#endif 
