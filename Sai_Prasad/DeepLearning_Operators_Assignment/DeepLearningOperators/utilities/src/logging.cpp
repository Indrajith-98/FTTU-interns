#include "logging.h"
#include <fstream>
#include <iostream>

void log_execution(const std::string& layer_name, const std::string& function, float execution_time, bool pass) {
    std::cout << "Execution started for " << layer_name << std::endl;

    std::ofstream log_file("../Report/execution_log/execution_log.txt", std::ios::app);
    if (!log_file) {
        std::cerr << "Error opening log file!" << std::endl;
        return;
    }

    log_file << "Layer: " << layer_name << "\n";
    log_file << "Function Executed: " << function << "\n";
    log_file << "Execution Time: " << execution_time << " seconds\n";
    log_file << "Pass/Fail: " << (pass ? "Pass" : "Fail") << "\n\n";
}
