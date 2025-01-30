#include <iostream>
#include "reverse.h"

int main() {
    std::string s1 = "debugging";
    std::string reversed = reverse(s1);
    std::cout << reversed << std::endl;
    return 0;
}