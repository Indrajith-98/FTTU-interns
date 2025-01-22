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
    for (int i = 0, j = n - 1; i < n / 2; i++, j--) {
        std::swap(s1[i], s1[j]);
    }
    for (int i = 0; i < n; i++) {
        std::cout << s1[i];
    }
    std::cout << std::endl;

    return 0;
}

