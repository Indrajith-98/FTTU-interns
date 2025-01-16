/*
Reverse the string
Given input:
debugging
Expected output:
gniggubed
*/
#include <iostream>
#include <string>

int main() {
    std::string s1 = "debugging";
    int n = s1.length();
    for (int i = 0; i < n/2; i++) {
        std::swap(s1[i], s1[n-i-1]); // Updated the code so that the right index decrements after every iteration
    }
    std::cout << s1 << std::endl;
    return 0;
}