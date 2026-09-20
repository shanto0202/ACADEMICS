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
        ll currentFlow = q.front().second;
        q.pop();

        for (ll child : adj[node])
        {
            if (parent[child] == -1 &&
                capacity[node][child] > 0)
            {
                parent[child] = node;

                ll newFlow =
                    min(currentFlow,
                        capacity[node][child]);

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
    V &capacity,
    V &originalCapacity,
    V &flow)
{
    ll maxFlow = 0;
    vector<ll> parent(n + 1);

    while (true)
    {
        ll pathFlow =
            bfs(
                source,
                sink,
                adj,
                capacity,
                parent);

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

            // Forward original edge
            if (originalCapacity[previous][node] > 0)
            {
                flow[previous][node] += pathFlow;
            }
            // Residual reverse edge: cancel previous flow
            else
            {
                flow[node][previous] -= pathFlow;
            }

            node = previous;
        }
    }

    return maxFlow;
}

// Finds one path using edges carrying positive flow.
bool findFlowPath(
    ll node,
    ll sink,
    V &flow,
    vector<ll> &path,
    vector<ll> &visited)
{
    if (node == sink)
    {
        return true;
    }

    visited[node] = 1;

    for (ll child = 1;
         child < (ll)flow.size();
         child++)
    {
        if (!visited[child] &&
            flow[node][child] > 0)
        {
            path.pb(child);

            if (findFlowPath(
                    child,
                    sink,
                    flow,
                    path,
                    visited))
            {
                // Consume this unit of flow so that
                // the edge is not reused by another path.
                flow[node][child]--;
                return true;
            }

            path.pop_back();
        }
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll testCases;
    cin >> testCases;

    for (ll cs = 1; cs <= testCases; cs++)
    {
        ll n, m;
        cin >> n >> m;

        ll source = 1;
        ll sink = n;

        V adj(n + 1);
        V capacity(
            n + 1,
            vector<ll>(n + 1, 0));

        V originalCapacity(
            n + 1,
            vector<ll>(n + 1, 0));

        V flow(
            n + 1,
            vector<ll>(n + 1, 0));

        loop(i, 0, m)
        {
            ll u, v;
            cin >> u >> v;

            adj[u].pb(v);
            adj[v].pb(u);

            // Each passage can be used once.
            capacity[u][v] += 1;
            originalCapacity[u][v] += 1;
        }

        ll maximumRoutes =
            edmondsKarp(
                n,
                source,
                sink,
                adj,
                capacity,
                originalCapacity,
                flow);

        cout << "Case "
             << cs
             << ": "
             << maximumRoutes
             << tata;

        if (maximumRoutes == 0)
        {
            cout
                << "No escape route possible! "
                << "The Professor needs a new plan."
                << tata;

            continue;
        }

        for (ll routeNumber = 1;
             routeNumber <= maximumRoutes;
             routeNumber++)
        {
            vector<ll> path;
            vector<ll> visited(n + 1, 0);

            path.pb(source);

            bool found =
                findFlowPath(
                    source,
                    sink,
                    flow,
                    path,
                    visited);

            if (found)
            {
                for (ll i = 0;
                     i < (ll)path.size();
                     i++)
                {
                    if (i > 0)
                    {
                        cout << " -> ";
                    }

                    cout << path[i];
                }

                cout << tata;
            }
        }
    }

    return 0;
}
