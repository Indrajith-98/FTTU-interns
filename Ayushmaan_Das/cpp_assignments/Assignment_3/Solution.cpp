/*ISSUES SPOTTED IN THE CODE:
- Line 32 dfs(): dfs(i-1, j, grid) is repated and called twice, one should be dfs(i+1, j, grid)
- Line 50: Maximum calculation is completely wrong. (max_number + 2 < val) ? val : max_number - 5 is unnecessary.
  Instead simply we can use max_number = max(max_number, val).

SOLUTION:
Modified the lines as per the above mentioned logics.
*/

#include <iostream>
#include <vector>
using namespace std;

int validate(int i, int j, vector<vector<int>> &grid)
{
    int rows = grid.size();
    int cols = grid[0].size();
    if (i >= rows || j >= cols || i < 0 || j < 0 || grid[i][j] == 0)
    {
        return 0;
    }
    return 1;
}

int dfs(int i, int j, vector<vector<int>> &grid)
{
    if (!validate(i, j, grid))
        return 0;
    grid[i][j] = 0;

    // CORRECTION MADE HERE
    return 1 + dfs(i - 1, j, grid) + dfs(i + 1, j, grid) + dfs(i, j + 1, grid) + dfs(i, j - 1, grid);
}

int maxAreaOfIsland(vector<vector<int>> &grid)
{
    int rows = grid.size();
    int cols = grid[0].size();
    int max_number = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] == 1)
            {
                int val = dfs(i, j, grid);

                // CORRECTION MADE HERE
                max_number = max(max_number, val);
            }
        }
    }
    return max_number;
}

void printIsland(vector<vector<int>> &grid)
{
    cout << "\nPrint the group" << endl;
    for (auto row : grid)
    {
        for (auto col : row)
        {
            cout << col << " ";
        }
        cout << endl;
    }
}

int main()
{
    // TESTING DATA (given) PASSED DIRECTLY (to avoid user input)
    vector<vector<int>> grid = {
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}};

    printIsland(grid);

    int max_area = maxAreaOfIsland(grid);

    std::cout << "Max area of Island: " << max_area << std::endl;
    return 0;
}
