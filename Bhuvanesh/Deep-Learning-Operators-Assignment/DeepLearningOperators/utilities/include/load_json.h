#ifndef LOAD_JSON_H
#define LOAD_JSON_H

#include <nlohmann/json.hpp>
#include <string>

nlohmann::json load_json(const std::string& file_path);

#endif 
