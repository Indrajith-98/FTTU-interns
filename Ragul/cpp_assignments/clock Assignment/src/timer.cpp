#include "timer.h"
#include <iostream>
#include <chrono>
#include <thread>

// Timer function
void timer() {
    int duration;
    std::cout << "Set timer duration (in seconds): ";
    std::cin >> duration;
    std::cout << "Timer started for " << duration << " seconds\n";
    for (int i = duration; i >= 0; --i) {
        std::cout << "\rTime remaining: " << i << " seconds..." << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }
    
    std::cout<<"-----------------------------------------------------------------------------------------------------------------------"<<std::endl;
    std::cout << "Time's up!\n";
    std::cout<<"-----------------------------------------------------------------------------------------------------------------------"<<std::endl;
}
