#include <bits/stdc++.h>
using namespace std;

void dfs(vector<vector<int>> &img, int x, int y, int oldColor, int newColor)
{
    if (x < 0 || x >= img.size() ||
        y < 0 || y >= img[0].size() ||
        img[x][y] != oldColor)
        return;

    img[x][y] = newColor;

    dfs(img, x + 1, y, oldColor, newColor);
    dfs(img, x - 1, y, oldColor, newColor);
    dfs(img, x, y + 1, oldColor, newColor);
    dfs(img, x, y - 1, oldColor, newColor);
}

vector<vector<int>> floodFill(vector<vector<int>> &img, int sr, int sc, int newColor)
{
    if (img[sr][sc] == newColor)
        return img;

    int oldColor = img[sr][sc];
    dfs(img, sr, sc, oldColor, newColor);

    return img;
}

int main()
{
    vector<vector<int>> img = {
        {1, 1, 1},
        {1, 1, 0},
        {1, 0, 1}};

    int sr = 1, sc = 1, newColor = 2;

    vector<vector<int>> res = floodFill(img, sr, sc, newColor);

    for (auto &row : res)
    {
        for (int x : row)
            cout << x << " ";
        cout << endl;
    }
}

/*
PROBLEM:

Given an image represented by a 2D grid of integers,
each value represents a pixel color.

You are given a starting pixel (sr, sc) and a new color.

Fill all connected pixels (4-directionally: up, down, left, right)
that have the same original color as the starting pixel
with the new color.

Example:

Input:
1 1 1
1 1 0
1 0 1

sr = 1, sc = 1, newColor = 2

Output:
2 2 2
2 2 0
2 0 1
*/