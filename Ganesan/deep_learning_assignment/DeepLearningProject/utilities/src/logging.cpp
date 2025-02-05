#include "logging.h"
#include <iostream>
#include <fstream>
#include <chrono>

void log_execution(const std::string& layer_name, bool success) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    std::ofstream log_file("report/execution.log", std::ios::app);
    log_file << "[" << std::ctime(&now_time) << "] Layer: " << layer_name
             << " Status: " << (success ? "PASS" : "FAIL") << std::endl;
}
