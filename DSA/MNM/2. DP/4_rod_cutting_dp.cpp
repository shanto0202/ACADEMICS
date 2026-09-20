#include <iostream>
#include <climits>
using namespace std;

// O (n^2)
int bottomUpCutRod(int price[], int n)
{
    int r[n + 1];
    r[0] = 0;
    for (int j = 1; j <= n; j++)
    {
        int q = INT_MIN;
        for (int i = 1; i <= j; i++)
        {
            q = max(q, price[i] + r[j - i]);
        }
        r[j] = q;
    }
    return r[n];
}

int main()
{
    int price[] = {0, 3, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int n = 10;
    cout << "Maximum Revenue = " << bottomUpCutRod(price, n);
    return 0;
}