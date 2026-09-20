#include <iostream>
#include <algorithm>
using namespace std;
// time complexity: O(m*n)
// space complexity: O(m*n)
int sequenceAlignment(string x, string y, int gap, int mismatch)
{
    int m = x.size();
    int n = y.size();
    int M[m + 1][n + 1]; // DP table storing minimum alignment cost
    // base case: align with gaps
    for (int i = 0; i <= m; i++)
    {
        M[i][0] = i * gap;
    }
    for (int j = 0; j <= n; j++)
    {
        M[0][j] = j * gap;
    }

    // AB
    // CB
    
    //   0  1  2
    // 0 0  2  4
    // 1 2  1  0
    // 2 4  0  0

    // fill DP table
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int cost = (x[i - 1] == y[j - 1]) ? 0 : mismatch; // match or mismatch //cost=1
            // choose minimum cost operation
            M[i][j] = min({cost + M[i - 1][j - 1], gap + M[i - 1][j], gap + M[i][j - 1]}); // OPT
        }
    }
    return M[m][n]; // final minimum alignment cost
}

int main()
{
    string x = "occurance";
    string y = "occurrence";
    cout << sequenceAlignment(x, y, 2, 1);
    return 0;
}

/*
KEY NOTES
1. Problem:
Sequence Alignment finds the minimum cost to convert one string into another.

2. DP Meaning:
M[i][j] = minimum alignment cost of first i characters of x and first j characters of y.

3. Operations:
Match      -> cost = 0
Mismatch   -> cost = mismatch
Gap        -> cost = gap (insertion or deletion)

4. Recurrence Relation:
M[i][j] = min(
    cost + M[i-1][j-1],   // diagonal match / mismatch
    gap  + M[i-1][j],     // insert gap in y
    gap  + M[i][j-1]      // insert gap in x
)

5. Base Case:
M[i][0] = i * gap
M[0][j] = j * gap

6. Complexity:
Time  = O(m*n)
Space = O(m*n)

7. Technique Used:
Dynamic Programming (Bottom-Up)
*/