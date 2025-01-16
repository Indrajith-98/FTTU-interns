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
#include <unordered_set>
using namespace std;

bool comparecount(pair<long, long> a, pair<long, long> b)
{
    return a.second > b.second;
}

vector<pair<long, long>> sortWithFrequency(vector<long> v1)
{

    vector<pair<long, long>> v2;
    int i = 0;

    std::unordered_set v1_set(v1.begin(), v1.end()); // LOG: implemented hashset to store unique elements of the array O(N * Log(N)) to O(N)

    while (i < v1_set.size()) // LOG: iterating only throught the unique elements of the array
    {
        pair<long, long> p;
        if (v2.size() == 0)
        {
            p.first = v1[i];
            p.second = count(v1.begin(), v1.end(), v1[i]);
            v2.push_back(p);
            i++;
            continue;
        }
        else if (v2[v2.size() - 1].first != v1[i])
        {
            p.first = v1[i];
            p.second = count(v1.begin(), v1.end(), v1[i]);
            v2.push_back(p);
            i++;
            continue;
        }
        i++;
    }
    sort(v2.begin(), v2.end(), comparecount);
    return v2;
}

int main()
{
    vector<long> v1{6, 5, 7, 5, 5, 6, 6, 6}; // LOG: creating an vector out of an array from the start of the array to the end.
    vector<pair<long, long>> v2 = sortWithFrequency(v1);
    vector<pair<long, long>>::iterator it = v2.begin();
    for (int i = 0; i != v2.size(); i++)
    {
        cout << v2[i].first << " " << v2[i].second << std::endl;
    }
    return 0;
}