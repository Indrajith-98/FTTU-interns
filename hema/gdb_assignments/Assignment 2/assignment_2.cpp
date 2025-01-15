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
    std::string s1 = "even";
    int n = s1.length();
    for (int i = 0,j=n-1; i < n/2; i++,j--) {
        std::swap(s1[i], s1[j]);
    }
    std::cout << s1 << std::endl;
    return 0;
}
