#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"

const ll INF = 4e18;

// ---------- Edge Structure ----------
struct Edge
{
    ll u, v, w;
};
// ---------- Modified Bellman-Ford ----------
bool bellmanFord(ll n, vector<Edge> &edges, ll source, ll k, vector<ll> &dist)
{
    vector<ll> noCoupon(n + 1, INF),usedCoupon(n + 1, INF);
    noCoupon[source] = 0;
    k = min(k, n - 1);
    for (ll i = 1; i <= k; i++)
    {
        vector<ll> nextNoCoupon = noCoupon;
        vector<ll> nextUsedCoupon = usedCoupon;
        bool changed = false;
        for (Edge e : edges)
        {
            if (noCoupon[e.u] != INF)
            {
                // Travel without using coupon
                if (nextNoCoupon[e.v] > noCoupon[e.u] + e.w)
                {
                    nextNoCoupon[e.v] = noCoupon[e.u] + e.w;
                    changed = true;
                }
                // Use coupon on this flight
                if (nextUsedCoupon[e.v] > noCoupon[e.u] + e.w / 2)
                {
                    nextUsedCoupon[e.v] = noCoupon[e.u] + e.w / 2;
                    changed = true;
                }
            }
            // Coupon was used earlier
            if (usedCoupon[e.u] != INF)
            {
                if (nextUsedCoupon[e.v] > usedCoupon[e.u] + e.w)
                {
                    nextUsedCoupon[e.v] = usedCoupon[e.u] + e.w;
                    changed = true;
                }
            }
        }
        noCoupon = nextNoCoupon;
        usedCoupon = nextUsedCoupon;
        if (!changed)
            break;
    }
    dist = usedCoupon;
    return dist[n] != INF;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m, k;
    cin >> n >> m >> k;
    vector<Edge> edges;
    for (ll i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;

        edges.pb({u, v, w});
    }
    vector<ll> dist;
    bool ok = bellmanFord(n, edges, 1, k, dist);
    if (!ok)
    {
        cout << "Not possible" << tata;
    }
    else
    {
        cout << dist[n] << tata;
    }
    return 0;
}