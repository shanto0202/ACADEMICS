#include <bits/stdc++.h>
using namespace std;

void dfs(int i, int j, vector<vector<char>>& g) {
    int n = g.size(), m = g[0].size();
    if (i<0 || j<0 || i>=n || j>=m || g[i][j]=='0') return;

    g[i][j] = '0';

    dfs(i+1,j,g);
    dfs(i-1,j,g);
    dfs(i,j+1,g);
    dfs(i,j-1,g);
}

int numIslands(vector<vector<char>>& grid) {
    int cnt = 0;
    for (int i=0;i<grid.size();i++) {
        for (int j=0;j<grid[0].size();j++) {
            if (grid[i][j]=='1') {
                dfs(i,j,grid);
                cnt++;
            }
        }
    }
    return cnt;
}

int main() {
    vector<vector<char>> grid = {
        {'1','1','0','0'},
        {'1','0','0','1'},
        {'0','0','1','1'},
        {'0','0','0','0'}
    };

    cout << numIslands(grid);
}

/*
PROBLEM:

Given a 2D grid of '1's (land) and '0's (water),
count the number of islands.

An island is surrounded by water and formed by connecting
adjacent lands horizontally or vertically.

Example:
Input:
1 1 0 0
1 0 0 1
0 0 1 1
0 0 0 0

Output: 3
*/