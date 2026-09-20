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

// ---------- Dijkstra with Coupon and Mandatory Edge ----------
vector<vector<vector<ll>>> dijkstra(ll n, vector<vector<pair<ll, ll>>> &adj, ll source, ll x, ll y, ll man_W)
{
    // dist[node][couponUsed][mandatoryUsed]
    vector<vector<vector<ll>>> dist(n + 1, vector<vector<ll>>(2, vector<ll>(2, INF)));
    // {distance, node, couponUsed, mandatoryUsed}
    priority_queue<tuple<ll, ll, ll, ll>, vector<tuple<ll, ll, ll, ll>>, greater<tuple<ll, ll, ll, ll>>> pq;

    dist[source][0][0] = 0;
    pq.push({0, source, 0, 0});

    while (!pq.empty())
    {
        auto [currentDist, node, couponUsed, mandatoryUsed] = pq.top();
        pq.pop();

        if (currentDist != dist[node][couponUsed][mandatoryUsed])
            continue;

        for (auto child : adj[node])
        {
            ll nextNode = child.first;
            ll weight = child.second;
            ll nextMandatoryUsed = mandatoryUsed;

            if (node == x && nextNode == y && weight == man_W)
            {
                nextMandatoryUsed = 1;
            }

            // ---------- Do not use coupon ----------
            if (dist[nextNode][couponUsed][nextMandatoryUsed] > dist[node][couponUsed][mandatoryUsed] + weight)
            {
                dist[nextNode][couponUsed][nextMandatoryUsed] = dist[node][couponUsed][mandatoryUsed] + weight;
                pq.push({dist[nextNode][couponUsed][nextMandatoryUsed], nextNode, couponUsed, nextMandatoryUsed});
            }

            // ---------- Use coupon ----------
            if (couponUsed == 0 && dist[nextNode][1][nextMandatoryUsed] > dist[node][0][mandatoryUsed] + weight / 2)
            {
                dist[nextNode][1][nextMandatoryUsed] = dist[node][0][mandatoryUsed] + weight / 2;
                pq.push({dist[nextNode][1][nextMandatoryUsed], nextNode, 1, nextMandatoryUsed});
            }
        }
    }
    return dist;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m, x, y, man_W;
    cin >> n >> m;
    vector<vector<pair<ll, ll>>> adj(n + 1);
    for (ll i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        adj[u].pb({v, w}); // directed edge
    }
    cin >> x >> y >> man_W;

    vector<vector<vector<ll>>> dist = dijkstra(n, adj, 1, x, y, man_W);
    // Mandatory edge must be used.
    // Coupon may be used or unused.
    ll ans = min(dist[n][0][1], dist[n][1][1]);
    if (ans == INF)
    {
        cout << "Not possible" << tata;
    }
    else
    {
        cout << ans << tata;
    }
    return 0;
}