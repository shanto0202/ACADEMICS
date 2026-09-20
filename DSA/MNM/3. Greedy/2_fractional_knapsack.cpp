#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int W = 50; // capacity
    vector<int> w = {10, 20, 30};   // weights
    vector<int> v = {60, 100, 120}; // values
    int n = w.size();

    // store (value/weight, index)
    vector<pair<double, int>> ratio;

    for (int i = 0; i < n; i++)
        ratio.push_back({(double)v[i] / w[i], i}); // 6, 5, 4

    // sort by descending ratio
    sort(ratio.begin(), ratio.end(), greater<>());

    double maxValue = 0;

    for (int i = 0; i < n; i++)
    {
        int idx = ratio[i].second;

        if (W >= w[idx])
        {
            maxValue += v[idx]; // take full item
            W -= w[idx];
        }
        else
        {
            maxValue += ratio[i].first * W; // take fraction
            break;
        }
    }

    cout << "Maximum value: " << maxValue;

    return 0;
}

/*
Key Notes:

1. Two types:
   - 0-1 Knapsack → cannot take fraction
   - Fractional Knapsack → can take fraction

2. Greedy Choice:
   Pick item with maximum (value / weight) ratio

3. Strategy:
   - sort items by v[i]/w[i] descending
   - take full item if possible
   - otherwise take fraction

4. Continue until:
   - capacity becomes 0

5. Example (from slide):
   W = 50
   w = [10,20,30], v = [60,100,120]

   → pick item 1, 2, and part of 3

6. Time Complexity:
   O(n log n) (sorting)

7. Why greedy works:
   Local best (max ratio) leads to global optimum
*/