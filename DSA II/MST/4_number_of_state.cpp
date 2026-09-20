//online(2022)
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"
#define loop(i, j, n) for (ll i = j; i < n; i++)

struct Edge
{
    ll u, v;
    double w;
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
        parent.resize(n);
        sz.assign(n, 1);

        for (ll i = 0; i < n; i++)
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
    double r;

    cin >> n >> r;

    vector<double> x(n), y(n);

    for (ll i = 0; i < n; i++)
    {
        cin >> x[i] >> y[i];
    }

    vector<Edge> edges;

    for (ll i = 0; i < n; i++)
    {
        for (ll j = i + 1; j < n; j++)
        {
            double dx = x[i] - x[j];
            double dy = y[i] - y[j];

            double dist = sqrt(dx * dx + dy * dy);

            edges.pb({i, j, dist});
        }
    }

    sort(edges.begin(), edges.end(), cmp);

    DSU dsu(n);

    double road = 0, railroad = 0;
    ll states = 1, edgeCount = 0;

    for (Edge e : edges)
    {
        if (dsu.unite(e.u, e.v))
        {
            if (e.w <= r)
            {
                road += e.w;
            }
            else
            {
                railroad += e.w;
                states++;
            }

            edgeCount++;

            if (edgeCount == n - 1)
                break;
        }
    }

    cout << states << " " << round(road) << " " << round(railroad) << tata;

    return 0;
}