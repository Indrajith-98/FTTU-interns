#include <iostream>
#include <ctime>

int main() {
    std::time_t currentTime = std::time(nullptr);
    std::cout << "Current time: " << std::ctime(&currentTime);
    return 0;
}