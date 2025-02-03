#ifndef LOGGING_H
#define LOGGING_H

#include <string>

void log_execution(const std::string& layer_name, const std::string& function, float execution_time, bool pass);

#endif 
