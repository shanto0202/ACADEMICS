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

// ---------------------------------------------------------
// Floyd-Warshall
// Negative edge allowed
// Negative cycle must not exist for valid shortest paths
// Time Complexity: O(n^3)
// Space Complexity: O(n^2)
// ---------------------------------------------------------
void floydWarshall(ll n, vector<vector<ll>> &dist)
{
    for (ll intermediate = 1; intermediate <= n; intermediate++)
    {
        for (ll source = 1; source <= n; source++)
        {
            for (ll destination = 1; destination <= n; destination++)
            {
                if (dist[source][intermediate] == INF ||
                    dist[intermediate][destination] == INF)
                {
                    continue;
                }

                dist[source][destination] =
                    min(dist[source][destination],
                        dist[source][intermediate] +
                            dist[intermediate][destination]);
            }
        }
    }
}

// ---------------------------------------------------------
// Floyd-Warshall With Path Reconstruction
// nextNode[u][v] = next node after u in shortest path u -> v
// ---------------------------------------------------------
void floydWarshallWithPath(
    ll n,
    vector<vector<ll>> &dist,
    vector<vector<ll>> &nextNode)
{
    for (ll intermediate = 1; intermediate <= n; intermediate++)
    {
        for (ll source = 1; source <= n; source++)
        {
            for (ll destination = 1; destination <= n; destination++)
            {
                if (dist[source][intermediate] == INF ||
                    dist[intermediate][destination] == INF)
                {
                    continue;
                }

                ll newDistance =
                    dist[source][intermediate] +
                    dist[intermediate][destination];

                if (newDistance < dist[source][destination])
                {
                    dist[source][destination] = newDistance;

                    // First node in source -> intermediate path
                    nextNode[source][destination] =
                        nextNode[source][intermediate];
                }
            }
        }
    }
}

// ---------------------------------------------------------
// Construct Shortest Path From Source To Destination
// Returns empty vector if no path exists
// ---------------------------------------------------------
vector<ll> constructPath(
    ll source,
    ll destination,
    vector<vector<ll>> &nextNode)
{
    vector<ll> path;

    if (nextNode[source][destination] == -1)
    {
        return path;
    }

    path.pb(source);

    while (source != destination)
    {
        source = nextNode[source][destination];
        path.pb(source);
    }

    return path;
}

// ---------------------------------------------------------
// Check If Floyd-Warshall Detected Any Negative Cycle
// If dist[i][i] < 0, a negative cycle exists
// ---------------------------------------------------------
bool hasNegativeCycle(ll n, vector<vector<ll>> &dist)
{
    for (ll node = 1; node <= n; node++)
    {
        if (dist[node][node] < 0)
        {
            return true;
        }
    }

    return false;
}

// ---------------------------------------------------------
// Dijkstra For One Source
// Used by Repeated Dijkstra
// ---------------------------------------------------------
vector<ll> dijkstra(
    ll n,
    vector<vector<pair<ll, ll>>> &adj,
    ll source)
{
    vector<ll> dist(n + 1, INF);

    priority_queue<
        pair<ll, ll>,
        vector<pair<ll, ll>>,
        greater<pair<ll, ll>>>
        pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty())
    {
        ll currentDistance = pq.top().first;
        ll node = pq.top().second;
        pq.pop();

        if (currentDistance != dist[node])
        {
            continue;
        }

        for (auto child : adj[node])
        {
            ll nextNode = child.first;
            ll weight = child.second;

            if (dist[nextNode] > dist[node] + weight)
            {
                dist[nextNode] = dist[node] + weight;
                pq.push({dist[nextNode], nextNode});
            }
        }
    }

    return dist;
}

// ---------------------------------------------------------
// APSP Using Repeated Dijkstra
// Only For Non-negative Weighted Graph
// Time Complexity: O(n * m log n)
// ---------------------------------------------------------
vector<vector<ll>> allPairsDijkstra(
    ll n,
    vector<vector<pair<ll, ll>>> &adj)
{
    vector<vector<ll>> allDistance(
        n + 1,
        vector<ll>(n + 1, INF));

    for (ll source = 1; source <= n; source++)
    {
        allDistance[source] = dijkstra(n, adj, source);
    }

    return allDistance;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    /*
    // =====================================================
    // Floyd-Warshall Basic Input Style
    // =====================================================

    ll n, m;
    cin >> n >> m;

    vector<vector<ll>> dist(
        n + 1,
        vector<ll>(n + 1, INF));

    // Distance from a node to itself is 0
    for (ll node = 1; node <= n; node++)
    {
        dist[node][node] = 0;
    }

    for (ll i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;

        // min is important if multiple edges exist
        dist[u][v] = min(dist[u][v], w);

        // For undirected graph:
        // dist[v][u] = min(dist[v][u], w);
    }

    floydWarshall(n, dist);

    if (hasNegativeCycle(n, dist))
    {
        cout << "NEGATIVE CYCLE" << tata;
    }
    else
    {
        for (ll source = 1; source <= n; source++)
        {
            for (ll destination = 1;
                 destination <= n;
                 destination++)
            {
                if (dist[source][destination] == INF)
                {
                    cout << "INF ";
                }
                else
                {
                    cout << dist[source][destination] << " ";
                }
            }

            cout << tata;
        }
    }
    */

    /*
    // =====================================================
    // Floyd-Warshall With Path Reconstruction
    // =====================================================

    ll n, m;
    cin >> n >> m;

    vector<vector<ll>> dist(
        n + 1,
        vector<ll>(n + 1, INF));

    vector<vector<ll>> nextNode(
        n + 1,
        vector<ll>(n + 1, -1));

    for (ll node = 1; node <= n; node++)
    {
        dist[node][node] = 0;
        nextNode[node][node] = node;
    }

    for (ll i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;

        if (w < dist[u][v])
        {
            dist[u][v] = w;
            nextNode[u][v] = v;
        }

        // For undirected graph:
        //
        // if (w < dist[v][u])
        // {
        //     dist[v][u] = w;
        //     nextNode[v][u] = u;
        // }
    }

    floydWarshallWithPath(n, dist, nextNode);

    ll source, destination;
    cin >> source >> destination;

    if (dist[source][destination] == INF)
    {
        cout << "NO PATH" << tata;
    }
    else
    {
        cout << "Distance: "
             << dist[source][destination]
             << tata;

        vector<ll> path =
            constructPath(source, destination, nextNode);

        cout << "Path: ";

        for (ll node : path)
        {
            cout << node << " ";
        }

        cout << tata;
    }
    */

    /*
    // =====================================================
    // Repeated Dijkstra Input Style
    // Only For Non-negative Edge Weights
    // =====================================================

    ll n, m;
    cin >> n >> m;

    vector<vector<pair<ll, ll>>> adj(n + 1);

    for (ll i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;

        adj[u].pb({v, w});

        // For undirected graph:
        // adj[v].pb({u, w});
    }

    vector<vector<ll>> dist =
        allPairsDijkstra(n, adj);

    for (ll source = 1; source <= n; source++)
    {
        for (ll destination = 1;
             destination <= n;
             destination++)
        {
            if (dist[source][destination] == INF)
            {
                cout << "INF ";
            }
            else
            {
                cout << dist[source][destination] << " ";
            }
        }

        cout << tata;
    }
    */

    return 0;
}

/*
===========================================================
APSP ALGORITHM SELECTION
===========================================================

1. Floyd-Warshall
   - Negative edge allowed
   - Negative cycle detection possible
   - Dense graph
   - Small n
   - Complexity: O(n^3)

2. Repeated Dijkstra
   - All edges must be non-negative
   - Sparse graph
   - Complexity: O(n * m log n)

3. Johnson's Algorithm
   - Negative edges allowed
   - No negative cycle
   - Sparse graph
   - Uses Bellman-Ford + Dijkstra
   - Learn only if included in syllabus

===========================================================
COMMON FLOYD-WARSHALL VARIATIONS
===========================================================

1. Basic all-pairs shortest distance
2. Shortest path reconstruction
3. Negative cycle detection
4. Transitive closure / reachability
5. Minimum cycle
6. Find city with smallest reachable neighbors
7. Add vertices one by one
8. Maximum bottleneck / minimax path
9. Probability path
10. Count or select intermediate vertices
*/