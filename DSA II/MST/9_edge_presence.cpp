// Check if edge (a, b) is part of any MST
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define tata "\n"

struct Edge
{
    ll u, v, w;
};

bool cmp(Edge a, Edge b)
{
    return a.w < b.w;
}

class DSU
{
public:
    vector<ll> parent, sz;

    DSU(ll n)
    {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);

        for (ll i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    ll find(ll x)
    {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    bool unite(ll a, ll b)
    {
        a = find(a);
        b = find(b);

        if (a == b)
            return false;

        if (sz[a] < sz[b])
            swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];

        return true;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    vector<Edge> edges;

    for (ll i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        edges.pb({u, v, w});
    }

    ll a, b;
    cin >> a >> b;

    ll targetW = -1;

    // Find weight of target edge (a, b)
    for (Edge e : edges)
    {
        if ((e.u == a && e.v == b) || (e.u == b && e.v == a))
        {
            targetW = e.w;
            break;
        }
    }

    if (targetW == -1)
    {
        cout << "False" << tata;
        return 0;
    }

    sort(edges.begin(), edges.end(), cmp);

    DSU dsu(n);

    // Only process edges with weight smaller than target edge
    for (Edge e : edges)
    {
        if (e.w < targetW)
        {
            dsu.unite(e.u, e.v);
        }
    }

    // If a and b already connected by smaller edges,
    // then target edge cannot be part of any MST.
    if (dsu.find(a) == dsu.find(b))
    {
        cout << "False" << tata;
    }
    else
    {
        cout << "True" << tata;
    }

    return 0;
}