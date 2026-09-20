#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define tata "\n"
#define V vector<vector<ll>>
#define loop(i, j, n) for (ll i = j; i < n; i++)

const ll INF = LLONG_MAX;

// Finds one shortest augmenting path.
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

// Edmonds-Karp maximum-flow function.
ll edmondsKarp(
    ll totalNodes,
    ll source,
    ll sink,
    V &adj,
    V &capacity)
{
    ll maxFlow = 0;

    vector<ll> parent(totalNodes);

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

// Adds a directed flow edge and its residual reverse edge.
void addEdge(
    ll u,
    ll v,
    ll cap,
    V &adj,
    V &capacity)
{
    adj[u].pb(v);
    adj[v].pb(u);

    capacity[u][v] += cap;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, e;
    cin >> n >> m >> e;

    ll source = 0;
    ll sink = n + m + 1;
    ll totalNodes = sink + 1;

    V adj(totalNodes);

    V capacity(
        totalNodes,
        vector<ll>(totalNodes, 0));

    // Source to every left-side node
    for (ll left = 1; left <= n; left++)
    {
        addEdge(
            source,
            left,
            1,
            adj,
            capacity);
    }

    // Every right-side node to sink
    for (ll right = 1; right <= m; right++)
    {
        ll rightNode = n + right;

        addEdge(
            rightNode,
            sink,
            1,
            adj,
            capacity);
    }

    // Possible left-right matching edges
    loop(i, 0, e)
    {
        ll left, right;
        cin >> left >> right;

        ll rightNode = n + right;

        addEdge(
            left,
            rightNode,
            1,
            adj,
            capacity);
    }

    ll maximumMatching =
        edmondsKarp(
            totalNodes,
            source,
            sink,
            adj,
            capacity);

    cout << maximumMatching << tata;

    return 0;
}
