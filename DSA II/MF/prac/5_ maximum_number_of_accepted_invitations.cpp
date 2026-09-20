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

    ll n, m;
    cin >> n >> m;

    ll source = 0;
    ll sink = n + m + 1;
    ll totalNodes = sink + 1;

    V adj(totalNodes);

    V capacity(
        totalNodes,
        vector<ll>(totalNodes, 0));

    // Source to every boy
    for (ll boy = 1; boy <= n; boy++)
    {
        addEdge(
            source,
            boy,
            1,
            adj,
            capacity);
    }

    // Every girl to sink
    for (ll girl = 1; girl <= m; girl++)
    {
        ll girlNode = n + girl;

        addEdge(
            girlNode,
            sink,
            1,
            adj,
            capacity);
    }

    // Read compatibility matrix
    loop(i, 0, n)
    {
        loop(j, 0, m)
        {
            ll possible;
            cin >> possible;

            if (possible == 1)
            {
                ll boyNode = i + 1;
                ll girlNode = n + j + 1;

                addEdge(
                    boyNode,
                    girlNode,
                    1,
                    adj,
                    capacity);
            }
        }
    }

    ll maximumInvitations =
        edmondsKarp(
            totalNodes,
            source,
            sink,
            adj,
            capacity);

    cout << maximumInvitations << tata;

    return 0;
}
