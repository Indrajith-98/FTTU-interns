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
        std::swap(s1[i], s1[n-i-1]); // Swapping logic with correct indices. Changed s[n-1] to s[n-i-1]
    }
    std::cout << s1 << std::endl;
    return 0;
}
