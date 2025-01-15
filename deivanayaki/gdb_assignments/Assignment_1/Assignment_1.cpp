/*
Program usage: sort the array of numbers based on it frequency in descending order
For the array input {6,5,7,5,5,6}, 
Expected output:
5 3
6 2
7 1
*/
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

bool comparecount(pair<long,long> a, pair<long,long> b) {
    return a.second > b.second;
}

vector<pair<long, long>> sortWithFrequency(vector<long> v1){
    
    vector<pair<long, long>> v2;
    int i = 0;
    
    sort(v1.begin(), v1.end());  // Include 0th index also for sorting

    while (i < v1.size()) {
        pair<long,long> p;   // Remove redundant codes
        if (v2.size() == 0 || v2[v2.size()-1].first != v1[i]) {
            p.first = v1[i];
            p.second = count(v1.begin(), v1.end(), v1[i]);
            v2.push_back(p);
        }
        i++;
    }
    sort(v2.begin(), v2.end(),  comparecount);  // Include 0th index also for sorting
    return v2;
}

int main() {
    long a[] = {6,5,7,5,5,6};
    vector<long> v1(a,a+6);
    vector<pair<long, long>> v2 = sortWithFrequency(v1); // Remove unused line
    for (int i =0; i != v2.size(); i++) {
        cout << v2[i].first << " " << v2[i].second << std::endl;
    }
    return 0;
}