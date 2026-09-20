#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"
#define V vector<vector<ll>>
#define loop(i, j, n) for (ll i = j; i < n; i++)
const ll INF = LLONG_MAX;
ll bfs(ll source, ll sink, V &adj, V &capacity, vector<ll> &parent)
{
    fill(parent.begin(), parent.end(), -1);
    parent[source] = -2;

    queue<pair<ll, ll>> q;
    q.push({source, INF});

    while (!q.empty())
    {
        ll node = q.front().first;
        ll flow = q.front().second;
        q.pop();

        for (ll child : adj[node])
        {
            if (parent[child] == -1 && capacity[node][child] > 0)
            {
                parent[child] = node;
                ll newFlow = min(flow, capacity[node][child]);

                if (child == sink)
                {
                    return newFlow;
                }

                q.push({child, newFlow});
            }
        }
    }

    return 0;
}
ll edmondsKarp(ll n, ll source, ll sink, V &adj, V &capacity)
{
    ll maxFlow = 0;
    vector<ll> parent(n + 1);

    while (true)
    {
        ll pathFlow = bfs(source, sink, adj, capacity, parent);

        if (pathFlow == 0)
        {
            break;
        }
        maxFlow += pathFlow;
        ll node = sink;
        while (node != source)
        {
            ll previous = parent[node];
            capacity[previous][node] -= pathFlow;
            capacity[node][previous] += pathFlow;
            node = previous;
        }
    }
    return maxFlow;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m, source, sink, ans = 0;
    cin >> n >> m >> source >> sink;
    V adj(n + 1), capacity(n + 1, vector<ll>(n + 1, 0));
    for (ll i = 0; i < m; i++)
    {
        ll u, v;
        cin >> u >> v;
        adj[u].pb(v);
        capacity[u][v]++;
    }
    ans = edmondsKarp(n, source, sink, adj, capacity);
    if (ans)
    {
        cout << ans << tata;
    }
    else
    {
        cout << -1 << tata;
    }
    return 0;
}