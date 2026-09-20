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
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        unordered_set<int> s(nums1.begin(), nums1.end());
        vector<int> ans;

        for (int x : nums2)
        {
            if (s.count(x))
            {
                ans.pb(x);
                s.erase(x); // Prevents duplicate output
            }
        }

        return ans;
    }
};
