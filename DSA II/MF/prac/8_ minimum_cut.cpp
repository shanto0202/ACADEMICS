#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define tata "\n"
#define V vector<vector<ll>>
#define loop(i, j, n) for (ll i = j; i < n; i++)

const ll INF = LLONG_MAX;

struct Edge
{
    ll u, v, c;
};

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
    vector<ll> parent(n + 1);

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

// Finds all vertices reachable from source
// in the final residual graph.
vector<ll> findReachable(
    ll n,
    ll source,
    V &adj,
    V &capacity)
{
    vector<ll> reachable(n + 1, 0);
    queue<ll> q;

    reachable[source] = 1;
    q.push(source);

    while (!q.empty())
    {
        ll node = q.front();
        q.pop();

        for (ll child : adj[node])
        {
            if (!reachable[child] &&
                capacity[node][child] > 0)
            {
                reachable[child] = 1;
                q.push(child);
            }
        }
    }

    return reachable;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    ll source, sink;
    cin >> source >> sink;

    V adj(n + 1);
    V capacity(n + 1, vector<ll>(n + 1, 0));

    vector<Edge> edges;

    loop(i, 0, m)
    {
        ll u, v, c;
        cin >> u >> v >> c;

        // Both directions are needed
        // for traversing residual reverse edges.
        adj[u].pb(v);
        adj[v].pb(u);

        // Handles multiple edges u -> v.
        capacity[u][v] += c;

        // Store original edge for min-cut output.
        edges.pb({u, v, c});
    }

    ll maxFlow =
        edmondsKarp(
            n,
            source,
            sink,
            adj,
            capacity);

    vector<ll> reachable =
        findReachable(
            n,
            source,
            adj,
            capacity);

    cout << "Maximum Flow: "
         << maxFlow << tata;

    // Reachable vertices form S.
    cout << "S = { ";

    for (ll node = 1; node <= n; node++)
    {
        if (reachable[node])
        {
            cout << node << " ";
        }
    }

    cout << "}" << tata;

    // Unreachable vertices form T.
    cout << "T = { ";

    for (ll node = 1; node <= n; node++)
    {
        if (!reachable[node])
        {
            cout << node << " ";
        }
    }

    cout << "}" << tata;

    cout << "Minimum Cut Edges:" << tata;

    ll minCutCapacity = 0;

    for (Edge e : edges)
    {
        // Original edge goes from S to T.
        if (reachable[e.u] &&
            !reachable[e.v])
        {
            cout << e.u << " -> "
                 << e.v
                 << " capacity "
                 << e.c << tata;

            minCutCapacity += e.c;
        }
    }

    cout << "Minimum Cut Capacity: "
         << minCutCapacity << tata;

    return 0;
}
