#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// O(d(n+k))
// Stable counting sort by digit (exp = 1, 10, 100...)
void countSort(vector<int> &A, int exp)
{
    int n = A.size();
    vector<int> out(n), cnt(10, 0);

    // count digit frequency
    for (int i = 0; i < n; i++)
        cnt[(A[i] / exp) % 10]++;

    // prefix sum → positions
    for (int i = 1; i < 10; i++)
        cnt[i] += cnt[i - 1];

    // build output (right → left for stability)
    for (int i = n - 1; i >= 0; i--)
    {
        int d = (A[i] / exp) % 10; //d=9
        out[--cnt[d]] = A[i];
    }

    A = out; // copy back
}

// Radix sort (LSD)
void radixSort(vector<int> &A)
{
    int mx = *max_element(A.begin(), A.end()); // O(n)

    // process each digit
    for (int exp = 1; mx / exp > 0; exp *= 10)
        countSort(A, exp);
}

int main()
{
    vector<int> A = {329, 457, 657, 839, 436, 720, 355};

    radixSort(A);

    for (int x : A)
        cout << x << " ";
}