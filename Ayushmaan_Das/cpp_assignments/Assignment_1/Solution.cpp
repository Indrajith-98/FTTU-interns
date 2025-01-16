/* CORRECTIONS MADE:
- Sorting of v1 and v2 were incorrect as +1 was unnecessary.
- Replace "long" with "int" (was giving memory issues)
- Line 31 was changed because if (v2.size() == 0) doesn't take into account the case where v1[i] has already been counted and added to v2 earlier.
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

    // INCORRECT SORTING ----------> Removed +1
    sort(v1.begin(), v1.end());

    while (i < v1.size())
    {
        pair<int, int> p;

        // CORRECTION -----------> Count occurrences of the element v1[i] and insert into v2
        if (v2.empty() || v2.back().first != v1[i])
        {
            p.first = v1[i];
            p.second = count(v1.begin(), v1.end(), v1[i]);
            v2.push_back(p);
        }
        i++;
    }

    // INCORRECT SORTING ----------> Removed +1
    sort(v2.begin(), v2.end(), comparecount);
    return v2;
}

int main()
{
    int a[] = {6, 5, 7, 5, 5, 6};
    vector<int> v1(a, a + 6);
    vector<pair<int, int>> v2 = sortWithFrequency(v1);
    for (int i = 0; i < v2.size(); i++)
    {
        cout << v2[i].first << " " << v2[i].second << endl;
    }
    return 0;
}
