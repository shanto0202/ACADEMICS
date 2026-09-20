//Online(2023)
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"

struct Planet
{
    ll x, y, z;
    ll id;
};

struct Edge
{
    ll u, v, w;
};

bool cmpEdge(Edge a, Edge b)
{
    return a.w < b.w;
}

bool cmpX(Planet a, Planet b)
{
    return a.x < b.x;
}

bool cmpY(Planet a, Planet b)
{
    return a.y < b.y;
}

bool cmpZ(Planet a, Planet b)
{
    return a.z < b.z;
}

ll cost(Planet a, Planet b)
{
    ll dx = abs(a.x - b.x);
    ll dy = abs(a.y - b.y);
    ll dz = abs(a.z - b.z);

    return min(dx, min(dy, dz));
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

    ll n;
    cin >> n;

    vector<Planet> planets(n);
    vector<Edge> edges;

    for (ll i = 0; i < n; i++)
    {
        planets[i].id = i;
        cin >> planets[i].x >> planets[i].y >> planets[i].z;
    }

    // Sort by x and add adjacent edges
    sort(planets.begin(), planets.end(), cmpX);

    for (ll i = 0; i < n - 1; i++)
    {
        ll u = planets[i].id;
        ll v = planets[i + 1].id;
        ll w = cost(planets[i], planets[i + 1]);

        edges.pb({u, v, w});
    }

    // Sort by y and add adjacent edges
    sort(planets.begin(), planets.end(), cmpY);

    for (ll i = 0; i < n - 1; i++)
    {
        ll u = planets[i].id;
        ll v = planets[i + 1].id;
        ll w = cost(planets[i], planets[i + 1]);

        edges.pb({u, v, w});
    }

    // Sort by z and add adjacent edges
    sort(planets.begin(), planets.end(), cmpZ);

    for (ll i = 0; i < n - 1; i++)
    {
        ll u = planets[i].id;
        ll v = planets[i + 1].id;
        ll w = cost(planets[i], planets[i + 1]);

        edges.pb({u, v, w});
    }

    // Kruskal
    sort(edges.begin(), edges.end(), cmpEdge);

    DSU dsu(n);

    ll ans = 0;
    ll edgeCount = 0;

    for (Edge e : edges)
    {
        if (dsu.unite(e.u, e.v))
        {
            ans += e.w;
            edgeCount++;

            if (edgeCount == n - 1)
                break;
        }
    }

    cout << ans << tata;

    return 0;
}