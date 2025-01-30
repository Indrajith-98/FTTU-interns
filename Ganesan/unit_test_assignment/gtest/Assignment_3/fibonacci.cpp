#include "fibonacci.h"
#include <vector>

std::vector<int> fibonacci(int n) {
    std::vector<int> fib = {0, 1};
    if (n <= 0) return {};
    if (n == 1) return {0};

    for (int i = 2; i < n; i++)
        fib.push_back(fib[i - 1] + fib[i - 2]);

    return fib;
}
