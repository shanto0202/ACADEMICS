#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"
const ll INF = 4e18;

struct Edge
{
    ll u, v, w;
};

// 2. Reach an emergency center using at most K roads
vector<ll> bellmanFord(ll n, vector<Edge> &edges, vector<ll> &centers, ll maxRoads)
{
    vector<ll> dist(n + 1, INF);
    for (ll center : centers)
    {
        dist[center] = 0;
    }
    maxRoads = min(maxRoads, n - 1);
    for (ll i = 1; i <= maxRoads; i++)
    {
        vector<ll> nextDist = dist;
        bool changed = false;
        for (Edge edge : edges)
        {
            if (dist[edge.u] != INF &&
                nextDist[edge.v] > dist[edge.u] + edge.w)
            {
                nextDist[edge.v] = dist[edge.u] + edge.w;
                changed = true;
            }
        }
        dist = nextDist;
        if (!changed)
            break;
    }
    return dist;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m, centerCount, maxRoads;
    cin >> n >> m >> centerCount >> maxRoads;
    vector<ll> centers(centerCount);
    for (ll &center : centers)
    {
        cin >> center;
    }
    vector<Edge> edges;
    for (ll i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        // Reverse edge
        edges.pb({v, u, w});
    }
    vector<ll> dist = bellmanFord(n, edges, centers, maxRoads);
    for (ll node = 1; node <= n; node++)
    {
        if (dist[node] == INF)
            cout << -1 << tata;
        else
            cout << dist[node] << tata;
    }
    return 0;
}