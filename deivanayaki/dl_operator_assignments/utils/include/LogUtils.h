#ifndef LOG_UTILS_H
#define LOG_UTILS_H

#include <string>

void logExecution(const std::string& imagePath, const std::string& layerName, const std::string& functionName, 
                  double executionTime, const std::string& status);

void unitTestLogExecution(const std::string& msg,const std::string& imagePath = "");

#endif 
