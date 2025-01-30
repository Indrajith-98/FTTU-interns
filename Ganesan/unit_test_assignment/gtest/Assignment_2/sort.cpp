#include "sort.h"
#include <algorithm>
#include <vector>
#include <utility>

bool comparecount(std::pair<long, long> a, std::pair<long, long> b) {
    return a.second > b.second;
}

std::vector<std::pair<long, long>> sortWithFrequency(std::vector<long> v1) {
    std::sort(v1.begin(), v1.end());
    std::vector<std::pair<long, long>> v2;
    int i = 0;

    while (i < v1.size()) {
        std::pair<long, long> p;
        if (v2.empty() || v2.back().first != v1[i]) {
            p.first = v1[i];
            p.second = std::count(v1.begin(), v1.end(), v1[i]);
            v2.push_back(p);
        }
        i++;
    }
    std::sort(v2.begin(), v2.end(), comparecount);
    return v2;
}
