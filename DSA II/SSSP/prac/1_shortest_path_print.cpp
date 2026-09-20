#include <bits/stdc++.h> // Compilation depends on included STL libraries
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"

const ll INF = 4e18;

// ---------- Edge Structure ----------
struct Edge
{
    ll u, v, w; // O(1) space per edge
};

// ---------- Bellman-Ford ----------
bool bellmanFord(ll n, vector<Edge> &edges, ll source, vector<ll> &dist, vector<ll> &parent, vector<ll> &parentWeight)
{
    dist.assign(n + 1, INF);       // O(V)
    parent.assign(n + 1, -1);      // O(V)
    parentWeight.assign(n + 1, 0); // O(V)

    dist[source] = 0; // O(1)

    for (ll i = 1; i < n; i++) // O(V) iterations
    {
        bool changed = false; // O(1)

        for (Edge e : edges) // O(E) per iteration
        {
            // O(1)
            if (dist[e.u] != INF && dist[e.v] > dist[e.u] + e.w)
            {
                dist[e.v] = dist[e.u] + e.w; // O(1)
                parent[e.v] = e.u;           // O(1)
                parentWeight[e.v] = e.w;     // O(1)

                changed = true; // O(1)
            }
        }

        if (!changed) // O(1)
            break;
    }

    // Negative cycle detection
    for (Edge e : edges) // O(E)
    {
        // O(1)
        if (dist[e.u] != INF && dist[e.v] > dist[e.u] + e.w)
        {
            return false; // O(1)
        }
    }

    return true; // Bellman-Ford total: O(VE), space: O(V)
}

// ---------- Print Shortest Path Edges ----------
void printPathbellman(ll source, ll target, vector<ll> &dist, vector<ll> &parent, vector<ll> &parentWeight)
{
    if (dist[target] == INF) // O(1)
    {
        cout << "No path" << tata;
        return;
    }

    vector<Edge> path;   // O(V) maximum space
    ll current = target; // O(1)

    while (current != source) // O(V) maximum
    {
        ll previous = parent[current]; // O(1)

        if (previous == -1) // O(1)
        {
            cout << "No path" << tata;
            return;
        }

        path.pb({previous, current, parentWeight[current]}); // O(1) amortized
        current = previous;                                  // O(1)
    }

    reverse(path.begin(), path.end()); // O(V)
    cout << "u v w: " << tata;

    for (Edge e : path) // O(V)
    {
        cout << e.u << " " << e.v << " " << e.w << tata;
    }

    // Total path printing: O(V)
}

// ---------- Dijkstra ----------
void dijkstra(ll n, vector<vector<pair<ll, ll>>> &adj, ll source, vector<ll> &dist, vector<ll> &parent, vector<ll> &parentWeight)
{
    dist.assign(n + 1, INF);       // O(V)
    parent.assign(n + 1, -1);      // O(V)
    parentWeight.assign(n + 1, 0); // O(V)

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;

    dist[source] = 0;     // O(1)
    pq.push({0, source}); // O(log V)

    while (!pq.empty()) // At most O(E) useful pushes/pops
    {
        ll currentDist = pq.top().first; // O(1)
        ll node = pq.top().second;       // O(1)
        pq.pop();                        // O(log V)

        if (currentDist != dist[node]) // O(1)
            continue;

        for (auto child : adj[node]) // Total O(E) over all processed nodes
        {
            ll nextNode = child.first; // O(1)
            ll weight = child.second;  // O(1)

            // O(1)
            if (dist[nextNode] > dist[node] + weight)
            {
                dist[nextNode] = dist[node] + weight; // O(1)
                parent[nextNode] = node;              // O(1)
                parentWeight[nextNode] = weight;      // O(1)

                pq.push({dist[nextNode], nextNode}); // O(log V)
            }
        }
    }

    // Dijkstra total: O((V + E) log V)
    // Space: O(V + E)
}

// ---------- Print Shortest Path Edges ----------
void printPathdijkstra(ll source, ll target, vector<ll> &dist, vector<ll> &parent, vector<ll> &parentWeight)
{
    if (dist[target] == INF) // O(1)
    {
        cout << "No path" << tata;
        return;
    }

    vector<Edge> path;   // O(V) maximum space
    ll current = target; // O(1)

    while (current != source) // O(V) maximum
    {
        ll previous = parent[current]; // O(1)

        if (previous == -1) // O(1)
        {
            cout << "No path" << tata;
            return;
        }

        path.pb({previous, current, parentWeight[current]}); // O(1) amortized
        current = previous;                                  // O(1)
    }

    reverse(path.begin(), path.end()); // O(V)

    cout << "Shortest distance: " << dist[target] << tata;
    cout << "u v w" << tata;

    for (Edge e : path) // O(V)
    {
        cout << e.u << " " << e.v << " " << e.w << tata;
    }

    // Total path printing: O(V)
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, source, target;
    cin >> n >> m >> source >> target; // O(1)

    // Bellman Ford
    vector<Edge> edges; // O(E) space

    for (ll i = 0; i < m; i++) // O(E)
    {
        ll u, v, w;
        cin >> u >> v >> w;  // O(1) per edge
        edges.pb({u, v, w}); // O(1) amortized
    }

    vector<ll> dist, parent, parentWeight;

    bool ok = bellmanFord(n, edges, source, dist, parent, parentWeight); // O(VE)

    if (!ok) // O(1)
    {
        cout << "NEGATIVE CYCLE" << tata;
    }
    else
    {
        printPathbellman(source, target, dist, parent, parentWeight); // O(V)
    }

    // Dijkstra
    vector<vector<pair<ll, ll>>> adj(n + 1); // O(V + E) space

    for (ll i = 0; i < m; i++) // O(E)
    {
        ll u, v, w;
        cin >> u >> v >> w; // O(1) per edge
        adj[u].pb({v, w});  // O(1) amortized

        // For undirected graph:
        // adj[v].pb({u, w});
    }

    vector<ll> dist, parent, parentWeight;

    dijkstra(n, adj, source, dist, parent, parentWeight);          // O((V + E) log V)
    printPathdijkstra(source, target, dist, parent, parentWeight); // O(V)

    return 0;
}