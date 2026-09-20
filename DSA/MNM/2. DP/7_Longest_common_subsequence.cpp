#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// time complexity O(mn)
// space complexity O(mn)
int LCS(string X, string Y)
{
    int m = X.length();
    int n = Y.length();
    int c[m + 1][n + 1];
    for (int i = 0; i <= m; i++)
    {
        c[i][0] = 0;
    }
    for (int j = 0; j <= n; j++)
    {
        c[0][j] = 0;
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
            }
            else
            {
                c[i][j] = max(c[i - 1][j], c[i][j - 1]);
            }
        }
    }
    return c[m][n];
}

int main()
{
    string X = "ABCBDAB";
    string Y = "BDCABA";
    cout << LCS(X, Y);
    return 0;
}