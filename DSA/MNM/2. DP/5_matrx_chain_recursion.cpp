#include <iostream>
#include <climits>
using namespace std;
//time complexity O(2^n)
int matrixChain(int p[], int i, int j)
{
    if (i == j)
    {
        return 0;
    }
    int ans = INT_MAX;
    for (int k = i; k < j; k++)
    {
        int q = matrixChain(p, i, k) + matrixChain(p, k + 1, j) + p[i - 1] * p[k] * p[j];
        ans = min(ans, q);
    }
    return ans;
}

int main()
{
    int p[] = {30, 35, 15, 5, 10, 20, 25};
    int n = 6;
    cout << matrixChain(p, 1, n);
    return 0;
}