#include <iostream>
#include <climits>
using namespace std;
//O(2^(n-1))
int cutRod(int price[], int n)
{
    if (n == 0)
    {
        return 0;
    }
    int q = INT_MIN;
    for (int i = 1; i <= n; i++)
    {
        q = max(q, price[i] + cutRod(price, n - i));
    }
    return q;
}

int main()
{
    int price[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int n = 10;
    cout << "Maximum Revenue = " << cutRod(price, n);
    return 0;
}