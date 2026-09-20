#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define tata "\n"

const ll INF = 4e18;

// 3. Reach an emergency center using a mandatory road
vector<ll> dijkstra(
    ll n,
    vector<vector<pair<ll, ll>>> &adj,
    vector<ll> sources)
{
    vector<ll> dist(n + 1, INF);

    priority_queue<
        pair<ll, ll>,
        vector<pair<ll, ll>>,
        greater<pair<ll, ll>>>
        pq;

    for (ll source : sources)
    {
        dist[source] = 0;
        pq.push({0, source});
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

    vector<vector<pair<ll, ll>>> reverseAdj(n + 1);

    for (ll i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;

        reverseAdj[v].pb({u, w});
    }

    ll x, y, mandatoryWeight;
    cin >> x >> y >> mandatoryWeight;

    vector<ll> toCenter =
        dijkstra(n, reverseAdj, centers);

    vector<ll> toX =
        dijkstra(n, reverseAdj, {x});

    for (ll node = 1; node <= n; node++)
    {
        if (toX[node] == INF || toCenter[y] == INF)
        {
            cout << -1 << tata;
        }
        else
        {
            cout << toX[node] + mandatoryWeight + toCenter[y] << tata;
        }
    }

    return 0;
}