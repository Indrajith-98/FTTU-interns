#include "json_handler.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

JsonHandler::JsonHandler(const std::string& filePath) : filePath(filePath) {}

bool JsonHandler::openJsonFile() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filePath << std::endl;
        return false;
    }
    try {
        file >> jsonData;
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return false;
    }
    file.close();
    return true;
}

nlohmann::json JsonHandler::getJsonData() const {
    return jsonData;
}
