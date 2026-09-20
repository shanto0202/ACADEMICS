#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"
#define V vector<vector<ll>>
#define loop(i, j, n) for (ll i = j; i < n; i++)
const ll INF = LLONG_MAX;

// BFS finds the shortest augmenting path in number of edges.
// Returns its bottleneck flow; returns 0 if sink is unreachable.
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

// Edmonds-Karp = Ford-Fulkerson using BFS.
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

        // Update forward and reverse residual capacities.
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

// DFS finds any augmenting path and updates its residual capacities.
// Returns the flow sent through that path; returns 0 if no path exists.
ll dfs(ll node, ll sink, ll flow, V &adj, V &capacity, vector<bool> &visited)
{
    if (node == sink)
    {
        return flow;
    }

    visited[node] = true;

    for (ll child : adj[node])
    {
        if (!visited[child] && capacity[node][child] > 0)
        {
            ll pathFlow = dfs(child, sink, min(flow, capacity[node][child]),
                              adj, capacity, visited);

            if (pathFlow > 0)
            {
                capacity[node][child] -= pathFlow;
                capacity[child][node] += pathFlow;
                return pathFlow;
            }
        }
    }

    return 0;
}

// Ford-Fulkerson using DFS.
ll fordFulkerson(ll n, ll source, ll sink, V &adj, V &capacity)
{
    ll maxFlow = 0;

    while (true)
    {
        vector<bool> visited(n + 1, false);
        ll pathFlow = dfs(source, sink, INF, adj, capacity, visited);

        if (pathFlow == 0)
        {
            break;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m;
    cin >> n >> m;

    // Assignment-style indexing: source = 0, sink = n - 1.
    // If source and sink are given, read them instead.
    ll source = 0, sink = n - 1;

    V adj(n + 1), capacity(n + 1, vector<ll>(n + 1, 0));

    for (ll i = 0; i < m; i++)
    {
        ll u, v, c;
        cin >> u >> v >> c;
        // Both directions are needed in the residual graph.
        adj[u].pb(v);
        adj[v].pb(u);
        // += handles multiple directed edges u -> v.
        capacity[u][v] += c;
    }
    // Use ONE of the following; both modify capacity.
    cout << edmondsKarp(n, source, sink, adj, capacity) << tata; // recommended
    // cout << fordFulkerson(n, source, sink, adj, capacity) << tata;
    return 0;
}

/*
===========================================================
EDMONDS-KARP
===========================================================

1. BFS runs only through edges with positive residual capacity.
2. The found path is shortest by number of edges.
3. pathFlow = minimum residual capacity on that path.
4. Forward residual capacity decreases by pathFlow.
5. Reverse residual capacity increases by pathFlow.

Time Complexity : O(V * E^2)
Space Complexity: O(V^2 + E) here, because a capacity matrix is used.

===========================================================
FORD-FULKERSON WITH DFS
===========================================================

1. DFS chooses any augmenting path.
2. With integer capacities, time complexity is O(E * maxFlow).
3. Edmonds-Karp is usually safer because its O(V * E^2) bound does not
   depend on the value of maxFlow.
*/
