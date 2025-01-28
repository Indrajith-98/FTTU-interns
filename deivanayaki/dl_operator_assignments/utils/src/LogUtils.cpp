#include "../include/LogUtils.h"
#include <fstream>
#include <ctime>
#include <chrono>
#include <iostream>

void logExecution(const std::string& imagePath, const std::string& layerName, const std::string& functionName, 
                  double executionTime, const std::string& status) {
    
    static bool imageLogged = false; 
    std::ofstream logFile("../Reports/execution.log", std::ios::app); 
    if (logFile.is_open()) {

        if (!imageLogged) {
            logFile << "\n\nImage Path: " << imagePath << std::endl;
            logFile << "----------------------------------------" << std::endl;
            imageLogged = true;  // Set the flag to true after logging the image path
        }
        std::time_t now = std::time(nullptr);
        logFile << std::asctime(std::localtime(&now)) << ": "
                << "Layer: " << layerName << ", "
                << "Function: " << functionName << ", "
                << "Time: " << executionTime << "ms, "
                << "Status: " << status << std::endl;
        logFile.close();
    } else {
        std::cerr << "Unable to open log file." << std::endl;
    }
}

void unitTestLogExecution(const std::string& msg,const std::string& imagePath)
{
    static bool imageLogged = false; 
    std::ofstream logFile("../Reports/dualTestResult.log", std::ios::app); 
    if (logFile.is_open()) {

        if (!imageLogged) {
            logFile << "\n\nImage Path: " << imagePath << std::endl;
            logFile << "----------------------------------------" << std::endl;
            imageLogged = true;  // Set the flag to true after logging the image path
        }
        std::time_t now = std::time(nullptr);
        logFile << std::asctime(std::localtime(&now)) << ": " << msg << "\n";
        logFile.close();
    }
    else {
        std::cerr << "Unable to open log file." << std::endl;
    }
}
