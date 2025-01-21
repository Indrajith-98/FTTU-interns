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
        std::swap(s1[i], s1[n-1-i]); //Here the indexing was changed
    }
    std::cout << s1 << std::endl;
    return 0;
}
