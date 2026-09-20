#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"
#define vrr(v, x, y) vector<vector<ll>> v(x, vector<ll>(y))
#define sajai(x) sort(x.begin(), x.end())
#define loop(i, j, n) for (ll i = j; i < n; i++)
#define in(v) loop(i, 0, v.size()) cin >> v[i]
#define out(v) loop(i, 0, v.size()) cout << v[i] << " "
#define yes cout << "YES" << tata
#define no cout << "NO" << tata

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> position;
        int n = nums.size();

        for (int i = 0; i < n; i++)
        {
            int need = target - nums[i];

            if (position.count(need))
            {
                return {position[need], i};
            }

            position[nums[i]] = i;
        }

        return {};
    }
};
