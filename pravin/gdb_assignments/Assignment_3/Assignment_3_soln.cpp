/*
Find the max area of the island
Input:
[
[0,0,1,0,0,0,0,1,0,0,0,0,0],
[0,0,0,0,0,0,0,1,1,1,0,0,0],
[0,1,1,0,1,0,0,0,0,0,0,0,0],
[0,1,0,0,1,1,0,0,1,0,1,0,0],
[0,1,0,0,1,1,0,0,1,1,1,0,0],
[0,0,0,0,0,0,0,0,0,0,1,0,0],
[0,0,0,0,0,0,0,1,1,1,0,0,0],
[0,0,0,0,0,0,0,1,1,0,0,0,0]
]
Output: 6 (Max area is 6)
*/

#include <iostream>
#include <vector>
using namespace std;

int validate(int i, int j, vector<vector<int> >& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    if (i >= rows or j >= cols or i < 0 or j < 0 or grid[i][j] == 0) {
        return 0;
    }
    return 1;
}

int dfs(int i, int j, vector<vector<int> >& grid) {
    if (!validate(i,j,grid)) return 0;
    grid[i][j] = 0;
    return 1 + dfs(i-1,j,grid) + dfs(i+1,j,grid) + dfs(i,j+1,grid) + dfs(i,j-1,grid);
}

int maxAreaOfIsland(vector<vector<int> >& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    int max_number = 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1) {
                int val  = dfs(i,j,grid);
                max_number = max(max_number, val);
            }
        }
    }    
    return max_number;
}

void printIsland(vector<vector<int> >& grid) {
    cout << "\nPrint the group" << endl;
    for (auto row: grid) {
        for(auto col: row) {
            cout << col << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int> > grid;
    int rows,cols;
    // Get inputs
    cout << "Enter the rows:" << endl;
    cin >> rows;
    cout << "Enter the cols:" << endl;
    cin >> cols;
    cout << "Enter content" << endl;
    for (int i = 0; i < rows; i++) {
        cout << "Enter " << i+1 << " row:" << endl;
        vector<int> row;
        for (int j = 0; j < cols; j++) {
            int val;
            cin >> val;
            row.push_back(val);
        }
        grid.push_back(row);
    }

    // Print the input
    printIsland(grid);

    // Get the max area
    int max_area = maxAreaOfIsland(grid);

    std::cout << "Max area of Island: " << max_area << std::endl;
    return 0;
}
