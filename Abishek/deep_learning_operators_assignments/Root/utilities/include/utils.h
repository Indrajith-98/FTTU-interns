#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

std::vector<float> load_binary_file(const std::string& file_path);

std::vector<float> loadImage(const std::string& filepath);

nlohmann::json load_json_config(const std::string& file_path);

#endif // UTILS_H