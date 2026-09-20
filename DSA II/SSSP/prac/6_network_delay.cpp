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
        ll currentDist = pq.top().first, node = pq.top().second;
        pq.pop();
        if (currentDist != dist[node])
        {
            continue;
        }
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

class Solution
{
public:
    ll networkDelayTime(vector<vector<int>> &times, int n, int k)
    {
        ll m = times.size();
        vector<vector<pair<ll, ll>>> adj(n + 1);
        for (ll i = 0; i < m; i++)
        {
            adj[times[i][0]].pb({times[i][1], times[i][2]});
        }
        vector<ll> dist = dijkstra(n, adj, k);
        ll ans = *max_element(dist.begin() + 1, dist.end());
        if (ans >= INF)
        {
            return -1;
        }
        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> v(m, vector<int>(3));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> v[i][j];
        }
    }
    Solution sol;
    cout << sol.networkDelayTime(v, n, k) << tata;
    return 0;
}