#ifndef JSON_HANDLER_H
#define JSON_HANDLER_H
#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

class JsonHandler {
public:
    JsonHandler(const std::string& filePath);

    bool openJsonFile();
    nlohmann::json getJsonData() const;

private:
    std::string filePath;
    nlohmann::json jsonData;
};

#endif // JSON_HANDLER_H