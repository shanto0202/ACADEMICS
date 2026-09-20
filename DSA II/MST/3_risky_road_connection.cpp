//online (2022)
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"

struct Edge
{
    ll u, v, w, eff;
};

bool cmpSafe(Edge a, Edge b)
{
    return a.w < b.w;
}

bool cmpRisky(Edge a, Edge b)
{
    return a.eff < b.eff;
}

class DSU
{
public:
    vector<ll> parent, sz, safeCnt;
    ll safeComp;

    DSU(ll n, vector<int> &risky)
    {
        parent.resize(n);
        sz.assign(n, 1);
        safeCnt.assign(n, 0);
        safeComp = 0;

        for (ll i = 0; i < n; i++)
        {
            parent[i] = i;

            if (!risky[i])
            {
                safeCnt[i] = 1;
                safeComp++;
            }
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

        // If both components contain safe cities,
        // then connecting them reduces safe component count.
        if (safeCnt[a] > 0 && safeCnt[b] > 0)
            safeComp--;

        parent[b] = a;
        sz[a] += sz[b];
        safeCnt[a] += safeCnt[b];

        return true;
    }

    bool allSafeConnected()
    {
        return safeComp <= 1;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, p;
    cin >> n >> m >> p;

    ll k;
    cin >> k;

    vector<int> risky(n, 0);

    for (ll i = 0; i < k; i++)
    {
        ll x;
        cin >> x;
        risky[x] = 1;
    }

    vector<Edge> safeEdges, riskyEdges;

    for (ll i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;

        ll riskyEndpoints = risky[u] + risky[v];
        ll effectiveWeight = w + p * riskyEndpoints;

        Edge e = {u, v, w, effectiveWeight};

        if (riskyEndpoints == 0)
            safeEdges.pb(e);
        else
            riskyEdges.pb(e);
    }

    sort(safeEdges.begin(), safeEdges.end(), cmpSafe);
    sort(riskyEdges.begin(), riskyEdges.end(), cmpRisky);

    DSU dsu(n, risky);

    vector<pair<ll, ll>> taken;
    ll totalCost = 0;

    // Phase 1: use only safe-safe edges
    for (Edge e : safeEdges)
    {
        if (dsu.unite(e.u, e.v))
        {
            taken.pb({e.u, e.v});
            totalCost += e.w;

            if (dsu.allSafeConnected())
                break;
        }
    }

    // Phase 2: use risky edges only if still needed
    if (!dsu.allSafeConnected())
    {
        for (Edge e : riskyEdges)
        {
            if (dsu.unite(e.u, e.v))
            {
                taken.pb({e.u, e.v});
                totalCost += e.eff;

                if (dsu.allSafeConnected())
                    break;
            }
        }
    }

    if (!dsu.allSafeConnected())
    {
        cout << -1 << tata;
    }
    else
    {
        cout << taken.size() << tata;

        for (auto edge : taken)
        {
            cout << edge.first << " " << edge.second << tata;
        }

        cout << totalCost << tata;
    }

    return 0;
}