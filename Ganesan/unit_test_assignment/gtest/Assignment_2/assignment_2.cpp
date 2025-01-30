#include <iostream>
#include <vector>
#include <utility>
#include "sort.h"

int main() {
    long a[] = {6, 5, 7, 5, 5, 6};
    std::vector<long> v1(a, a + 6);
    std::vector<std::pair<long, long>> v2 = sortWithFrequency(v1);

    for (const auto& p : v2) {
        std::cout << p.first << " " << p.second << std::endl;
    }
    return 0;
}
