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

// ---------- Dijkstra for Non-negative Weighted Graph ----------
vector<ll> dijkstra(ll n, vector<vector<pair<ll, ll>>> &adj, ll source)
{
    vector<ll> dist(n + 1, INF);

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;

    dist[source] = 0;
    pq.push({0, source});

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

// ---------- Bellman-Ford for Negative Edge Weighted Graph ----------
bool bellmanFord(ll n, vector<Edge> &edges, ll source, vector<ll> &dist)
{
    dist.assign(n + 1, INF);
    dist[source] = 0;

    for (ll i = 1; i <= n - 1; i++)
    {
        bool changed = false;

        for (Edge e : edges)
        {
            if (dist[e.u] != INF && dist[e.v] > dist[e.u] + e.w)
            {
                dist[e.v] = dist[e.u] + e.w;
                changed = true;
            }
        }

        if (!changed)
            break;
    }

    for (Edge e : edges)
    {
        if (dist[e.u] != INF && dist[e.v] > dist[e.u] + e.w)
        {
            return false; // negative cycle reachable from source
        }
    }

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, source, k;
    cin >> n >> m >> k;
    vector<ll> v(k);
    for (ll i = 0; i < k; i++)
    {
        cin >> v[i];
    }
    vector<Edge> edges, E;

    for (ll i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        edges.pb({u, v, w}); // directed edge
    }

    vector<ll> dist, D;

    for (int i = 1; i <= n; i++)
    {
        ll p = 1, m1 = LLONG_MAX;
        for (int j = 0; j < k; j++)
        {
            bool ok = bellmanFord(n, edges, i, dist);
            if (ok)
            {
                m1 = min(m1, dist[v[j]]);
                p = 0;
            }
        }
        if (p)
        {
            cout << -1 << tata;
        }
        else
        {
            cout << m1 << tata;
        }
    }

    return 0;
}