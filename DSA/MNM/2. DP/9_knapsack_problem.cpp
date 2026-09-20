#include <iostream>
#include <algorithm>
using namespace std;

// 0/1 Knapsack using Dynamic Programming
// Time Complexity: O(n * W)
// Space Complexity: O(n * W)

int knapsack(int W, int wt[], int val[], int n)
{
    int M[n + 1][W + 1]; // DP table: max value for i items and capacity w
    
    // base case: if no items, value = 0
    for (int w = 0; w <= W; w++)
    {
        M[0][w] = 0;
    }
    // build table row by row
    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            // if current item's weight exceeds capacity
            if (wt[i - 1] > w)
            {
                M[i][w] = M[i - 1][w]; // cannot include item
            }
            else
            {
                // choose max of excluding or including the item
                M[i][w] = max(M[i - 1][w], val[i - 1] + M[i - 1][w - wt[i - 1]]);
            }
        }
    }
    return M[n][W]; // maximum value for n items and capacity W
}

int main()
{
    int val[] = {1, 6, 18, 22, 28}; // values of items
    int wt[] = {1, 2, 5, 6, 7};     // weights of items

    int W = 11; // maximum capacity of knapsack
    int n = 5;  // number of items

    cout << knapsack(W, wt, val, n);

    return 0;
}

/*
Knapsack DP Table Example

Items:
value = {1, 6, 18, 22, 28}
weight = {1, 2, 5, 6, 7}

Columns → weight limit (capacity)
Rows → number of items considered

        w →
i↓      0  1  2  3  4  5  6  7
--------------------------------
0       0  0  0  0  0  0  0  0
1       0  1  1  1  1  1  1  1
2       0  1  6  7  7  7  7  7
3       0  1  6  7  7  18 19 25
4       0  1  6  7  7  18 22 23
5       0  1  6  7  7  18 22 28

Meaning:
M[i][w] = maximum value using first i items with capacity w


KEY NOTES

1. Problem:
0/1 Knapsack selects items to maximize total value without exceeding capacity.
Each item can be chosen either 0 or 1 time.

2. DP Meaning:
M[i][w] = maximum value achievable using first i items with capacity w.

3. Decision:
For each item we have two choices:
- Exclude the item
- Include the item (if weight allows)

4. Recurrence Relation:
M[i][w] = max(
    M[i-1][w],                          // exclude item
    val[i-1] + M[i-1][w - wt[i-1]]      // include item
)

5. Base Case:
M[0][w] = 0
(no items → no value)

6. Complexity:
Time  = O(n * W)
Space = O(n * W)

7. Technique Used:
Dynamic Programming (Bottom-Up)
*/