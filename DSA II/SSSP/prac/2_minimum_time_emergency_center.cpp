#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define tata "\n"

const ll INF = 4e18;

// 1. Minimum time from any emergency center to every city
vector<ll> dijkstra(
    ll n,
    vector<vector<pair<ll, ll>>> &adj,
    vector<ll> &centers)
{
    vector<ll> dist(n + 1, INF);

    priority_queue<
        pair<ll, ll>,
        vector<pair<ll, ll>>,
        greater<pair<ll, ll>>>
        pq;

    for (ll center : centers)
    {
        dist[center] = 0;
        pq.push({0, center});
    }

    while (!pq.empty())
    {
        auto [currentDist, node] = pq.top();
        pq.pop();

        if (currentDist != dist[node])
            continue;

        for (auto [nextNode, weight] : adj[node])
        {
            if (dist[nextNode] > currentDist + weight)
            {
                dist[nextNode] = currentDist + weight;
                pq.push({dist[nextNode], nextNode});
            }
        }
    }

    return dist;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, k;
    cin >> n >> m >> k;

    vector<ll> centers(k);

    for (ll &center : centers)
        cin >> center;

    vector<vector<pair<ll, ll>>> adj(n + 1);

    for (ll i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;

        adj[u].pb({v, w});
    }

    vector<ll> dist = dijkstra(n, adj, centers);

    for (ll node = 1; node <= n; node++)
    {
        if (dist[node] == INF)
            cout << -1 << tata;
        else
            cout << dist[node] << tata;
    }

    return 0;
}