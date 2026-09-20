#include <iostream>
#include <climits>
using namespace std;
// time complexity O(n^3)
// space complexity O(n^2)
void matrixChainOrder(int p[], int n)
{
    int m[n + 1][n + 1];
    for (int i = 1; i <= n; i++)
    {
        m[i][i] = 0;
    }
    for (int l = 2; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
            {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                m[i][j] = min(m[i][j], q);
            }
        }
    }
    cout << m[1][n];
}

int main()
{
    int p[] = {30, 35, 15, 5, 10, 20, 25};
    int n = 6;
    matrixChainOrder(p, n);
    return 0;
}