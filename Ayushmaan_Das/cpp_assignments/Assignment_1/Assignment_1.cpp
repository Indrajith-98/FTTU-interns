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

bool comparecount(pair<int, int> a, pair<int, int> b)
{
    return a.second > b.second;
}

vector<pair<int, int>> sortWithFrequency(vector<int> v1)
{

    vector<pair<int, int>> v2;
    int i = 0;

    sort(v1.begin() + 1, v1.end());

    while (i < v1.size())
    {
        pair<int, int> p;
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
    sort(v2.begin() + 1, v2.end(), comparecount);
    return v2;
}

int main()
{
    int a[] = {6, 5, 7, 5, 5, 6};
    vector<int> v1(a, a + 6);
    vector<pair<int, int>> v2 = sortWithFrequency(v1);
    vector<pair<int, int>>::iterator it = v2.begin();
    for (int i = 0; i != v2.size(); i++)
    {
        cout << v2[i].first << " " << v2[i].second << std::endl;
    }
    return 0;
}