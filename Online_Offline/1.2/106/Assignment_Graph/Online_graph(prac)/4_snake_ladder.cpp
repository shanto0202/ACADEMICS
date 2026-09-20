#include <bits/stdc++.h>
using namespace std;

// Function to find minimum dice throws
int getMinDiceThrows(vector<int> &move)
{
    int n = move.size();
    vector<bool> visited(n, false);
    queue<pair<int, int>> q;

    visited[0] = true;
    q.push({0, 0}); // {cell, dice throws}

    while (!q.empty())
    {
        auto [v, dist] = q.front();
        q.pop();

        if (v == n - 1)
            return dist;

        for (int j = v + 1; j <= v + 6 && j < n; j++)
        {
            if (!visited[j])
            {
                visited[j] = true;

                int dest = (move[j] != -1) ? move[j] : j;
                q.push({dest, dist + 1});
            }
        }
    }
    return -1;
}

int main()
{
    int n = 30;
    vector<int> moves(n, -1);

    // Ladders
    moves[2] = 21;
    moves[4] = 7;
    moves[10] = 25;
    moves[19] = 28;

    // Snakes
    moves[26] = 0;
    moves[20] = 8;
    moves[16] = 3;
    moves[18] = 6;

    cout << getMinDiceThrows(moves);
}

/*
PROBLEM:

You are given a Snakes and Ladders board of size N cells (0 to N-1).

- Each cell may contain:
  - -1 → normal cell
  - A number → destination of snake or ladder

Rules:
- You start at cell 0
- You can roll a dice (1 to 6)
- From current cell v, you can go to v+1 ... v+6
- If a cell has a ladder or snake, you must move to its destination

Goal:
Find the minimum number of dice throws required to reach cell N-1.

Example:
Board size = 30

Ladders:
2 → 21
4 → 7
10 → 25
19 → 28

Snakes:
26 → 0
20 → 8
16 → 3
18 → 6

Output:
Minimum number of dice throws to reach the last cell.
*/