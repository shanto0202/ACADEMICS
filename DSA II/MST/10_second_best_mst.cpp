#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define tata "\n"

struct Edge
{
    ll u, v, w, id;
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

ll kruskal(ll n, vector<Edge> &edges, ll skipId, vector<ll> &usedEdges)
{
    DSU dsu(n);

    ll cost = 0;
    ll edgeCount = 0;

    for (Edge e : edges)
    {
        if (e.id == skipId)
            continue;

        if (dsu.unite(e.u, e.v))
        {
            cost += e.w;
            edgeCount++;

            if (skipId == -1)
            {
                usedEdges.pb(e.id);
            }

            if (edgeCount == n - 1)
                break;
        }
    }

    if (edgeCount != n - 1)
        return LLONG_MAX;

    return cost;
}

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

        edges.pb({u, v, w, i});
    }

    sort(edges.begin(), edges.end(), cmp);

    vector<ll> usedEdges;

    ll mstCost = kruskal(n, edges, -1, usedEdges);

    if (mstCost == LLONG_MAX)
    {
        cout << -1 << tata;
        return 0;
    }

    ll secondBest = LLONG_MAX;

    for (ll id : usedEdges)
    {
        vector<ll> temp;

        ll newCost = kruskal(n, edges, id, temp);

        if (newCost > mstCost)
        {
            secondBest = min(secondBest, newCost);
        }
    }

    if (secondBest == LLONG_MAX)
        cout << -1 << tata;
    else
        cout << secondBest << tata;

    return 0;
}