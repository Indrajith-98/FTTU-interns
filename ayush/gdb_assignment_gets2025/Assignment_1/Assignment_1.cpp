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
    return a.second > b.second; // here Sorted by frequency in descending order
}

vector<pair<long, long>> sortWithFrequency(vector<long> v1) {
    vector<pair<long, long>> v2;
    sort(v1.begin(), v1.end()); // here Sorted the entire vector

    for (size_t i = 0; i < v1.size();) {
        pair<long, long> p;
        p.first = v1[i];
        p.second = count(v1.begin(), v1.end(), v1[i]); // here Counted occurrences of the current number
        v2.push_back(p);
        i += p.second; //here Skipped all occurrences of the same number
    }

    sort(v2.begin(), v2.end(), comparecount); // Here Sorted by frequency in descending order
    return v2;
}

int main() {
    long a[] = {6, 5, 7, 5, 5, 6};
    vector<long> v1(a, a + 6);
    vector<pair<long, long>> v2 = sortWithFrequency(v1);

    for (size_t i = 0; i < v2.size(); ++i) {
        cout << v2[i].first << " " << v2[i].second << endl;
    }
    return 0;
}

