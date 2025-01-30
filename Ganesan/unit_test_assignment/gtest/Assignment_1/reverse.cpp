#include "reverse.h"
#include <algorithm>

std::string reverse(const std::string& s1) {
    std::string reversed = s1;
    int n = reversed.length();
    for (int i = 0; i < n / 2; i++) {
        std::swap(reversed[i], reversed[(n - 1) - i]);
    }
    return reversed;
}