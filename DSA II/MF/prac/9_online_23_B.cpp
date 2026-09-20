#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define tata "\n"
#define V vector<vector<ll>>
#define loop(i, j, n) for (ll i = j; i < n; i++)

const ll INF = LLONG_MAX;

struct Proposal
{
    ll u, v, c;
};

// Finds one augmenting path in the residual graph.
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

// Standard Edmonds-Karp.
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

// Marks every node reachable from source
// through positive residual-capacity edges.
vector<ll> findReachableFromSource(
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

// Marks every node from which sink is reachable
// through positive residual-capacity edges.
//
// We start from sink and traverse residual edges backwards.
vector<ll> findCanReachSink(
    ll n,
    ll sink,
    V &adj,
    V &capacity)
{
    vector<ll> canReachSink(n + 1, 0);
    queue<ll> q;

    canReachSink[sink] = 1;
    q.push(sink);

    while (!q.empty())
    {
        ll node = q.front();
        q.pop();

        for (ll previous : adj[node])
        {
            // previous -> node is a positive residual edge.
            if (!canReachSink[previous] &&
                capacity[previous][node] > 0)
            {
                canReachSink[previous] = 1;
                q.push(previous);
            }
        }
    }

    return canReachSink;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    ll source = 1;
    ll sink = n;

    V adj(n + 1);
    V capacity(n + 1, vector<ll>(n + 1, 0));

    loop(i, 0, m)
    {
        ll u, v, c;
        cin >> u >> v >> c;

        // Both directions are needed for residual traversal.
        adj[u].pb(v);
        adj[v].pb(u);

        // Handles multiple edges u -> v.
        capacity[u][v] += c;
    }

    ll p;
    cin >> p;

    vector<Proposal> proposals(p);

    loop(i, 0, p)
    {
        cin >> proposals[i].u
            >> proposals[i].v
            >> proposals[i].c;
    }

    // Construct the final residual graph.
    ll maxFlow =
        edmondsKarp(
            n,
            source,
            sink,
            adj,
            capacity);

    vector<ll> reachableFromSource =
        findReachableFromSource(
            n,
            source,
            adj,
            capacity);

    vector<ll> canReachSink =
        findCanReachSink(
            n,
            sink,
            adj,
            capacity);

    vector<ll> answer;

    loop(i, 0, p)
    {
        ll u = proposals[i].u;
        ll v = proposals[i].v;
        ll c = proposals[i].c;

        if (c > 0 &&
            reachableFromSource[u] &&
            canReachSink[v])
        {
            // Proposal indices are 1-based.
            answer.pb(i + 1);
        }
    }

    if (answer.empty())
    {
        cout << "None" << tata;
    }
    else
    {
        for (ll index : answer)
        {
            cout << index << " ";
        }

        cout << tata;
    }

    return 0;
}
