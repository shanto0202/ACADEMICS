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

// ---------- Multi-source Dijkstra ----------
vector<ll> dijkstra(ll n, vector<vector<pair<ll, ll>>> &adj, vector<ll> &sources)
{
    vector<ll> dist(n + 1, INF);

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;

    // Start from all emergency centers
    for (ll source : sources)
    {
        dist[source] = 0;
        pq.push({0, source});
    }

    while (!pq.empty())
    {
        ll currentDist = pq.top().first;
        ll node = pq.top().second;
        pq.pop();

        if (currentDist != dist[node])
            continue;

        for (auto child : adj[node])
        {
            ll nextNode = child.first;
            ll weight = child.second;

            if (dist[nextNode] > dist[node] + weight)
            {
                dist[nextNode] = dist[node] + weight;
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

    for (ll i = 0; i < k; i++)
    {
        cin >> centers[i];
    }
    vector<vector<pair<ll, ll>>> adj(n + 1);

    for (ll i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        // Original edge: u -> v
        // Reversed edge: v -> u
        adj[v].pb({u, w});
    }

    vector<ll> dist = dijkstra(n, adj, centers);

    for (ll i = 1; i <= n; i++)
    {
        if (dist[i] == INF)
            cout << -1 << tata;
        else
            cout << dist[i] << tata;
    }
    return 0;
}