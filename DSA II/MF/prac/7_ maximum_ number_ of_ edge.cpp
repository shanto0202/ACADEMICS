#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define tata "\n"
#define V vector<vector<ll>>
#define loop(i, j, n) for (ll i = j; i < n; i++)

const ll INF = LLONG_MAX;

ll bfs(
    ll source,
    ll sink,
    V &adj,
    V &capacity,
    vector<ll> &parent)
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
            if (parent[child] == -1 &&
                capacity[node][child] > 0)
            {
                parent[child] = node;

                ll newFlow =
                    min(flow, capacity[node][child]);

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

ll edmondsKarp(
    ll n,
    ll source,
    ll sink,
    V &adj,
    V &capacity)
{
    ll maxFlow = 0;
    vector<ll> parent(n);

    while (true)
    {
        ll pathFlow =
            bfs(source, sink, adj, capacity, parent);

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

    ll n, m;
    cin >> n >> m;

    ll source, sink;
    cin >> source >> sink;

    V adj(n);
    V capacity(n, vector<ll>(n, 0));

    loop(i, 0, m)
    {
        ll u, v;
        cin >> u >> v;

        adj[u].pb(v);
        adj[v].pb(u);

        // Each original edge can be used by at most one path.
        capacity[u][v] += 1;
    }

    ll maximumPaths =
        edmondsKarp(
            n,
            source,
            sink,
            adj,
            capacity);

    if (maximumPaths == 0)
    {
        cout << -1 << tata;
    }
    else
    {
        cout << maximumPaths << tata;
    }

    return 0;
}
