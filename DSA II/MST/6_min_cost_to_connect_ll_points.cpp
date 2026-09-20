//Leetcode medium
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"
#define vr(v, x) vector<ll> v(x)
#define vrr(v, x, y) vector<vector<ll>> v(x, vector<ll>(y))
#define sajai(x) sort(x.begin(), x.end())
#define rsort(a) sort(a.begin(), a.end(), greater<>())
#define ulta(a) reverse(a.begin(), a.end())
#define mucho(a, j) a.erase(a.begin() + j)
#define choto(a) *min_element(a.begin(), a.end())
#define boro(a) *max_element(a.begin(), a.end())
#define jog(a) accumulate(a.begin(), a.end(), 0LL)
#define bit(n) __builtin_popcountll(n)
#define loop(i, j, n) for (ll i = j; i < n; i++)
#define in(v) loop(i, 0, v.size()) cin >> v[i]
#define out(v) loop(i, 0, v.size()) cout << v[i] << " "
struct Edge
{
    int u, v, w;
};

bool cmp(Edge a, Edge b)
{
    return a.w < b.w;
}

class DSU
{
public:
    vector<int> parent, sz;

    DSU(ll n)
    {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);

        for (ll i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b)
    {
        a = find(a);
        b = find(b);

        if (a == b)
        {
            return false;
        }

        if (sz[a] < sz[b])
        {
            swap(a, b);
        }

        parent[b] = a;
        sz[a] += sz[b];

        return true;
    }
};

class Solution
{
public:
    int minCostConnectPoints(vector<vector<int>> &points)
    {
        int n, m, u, v, w, ans = 0, edgeCount = 0;
        n = points.size();
        vector<Edge> edges;
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                int d = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                edges.pb({i, j, d});
            }
        }
        sort(edges.begin(), edges.end(), cmp);
        DSU dsu(n);
        for (Edge e : edges)
        {
            if (dsu.unite(e.u, e.v))
            {
                ans += e.w;
                if (edgeCount == n - 1)
                {
                    break;
                }
            }
        }
        return ans;
    }
};