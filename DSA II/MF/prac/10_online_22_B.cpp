#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define tata "\n"
#define V vector<vector<ll>>
#define loop(i, j, n) for (ll i = j; i < n; i++)

const ll INF = LLONG_MAX;

struct Point
{
    double x, y;
};

struct Hole
{
    double x, y;
    ll capacity;
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

bool canReach(
    Point mouse,
    Hole hole,
    double radius)
{
    double dx = mouse.x - hole.x;
    double dy = mouse.y - hole.y;

    double distanceSquared =
        dx * dx + dy * dy;

    double radiusSquared =
        radius * radius;

    const double EPS = 1e-9;

    return distanceSquared <= radiusSquared + EPS;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll testCases;
    cin >> testCases;

    for (ll cs = 1; cs <= testCases; cs++)
    {
        ll miceCount, holeCount;
        double radius;

        cin >> miceCount
            >> holeCount
            >> radius;

        vector<Point> mice(miceCount);
        vector<Hole> holes(holeCount);

        loop(i, 0, miceCount)
        {
            cin >> mice[i].x
                >> mice[i].y;
        }

        loop(i, 0, holeCount)
        {
            cin >> holes[i].x
                >> holes[i].y
                >> holes[i].capacity;
        }

        ll source = 0;
        ll sink = miceCount + holeCount + 1;
        ll totalNodes = sink + 1;

        V adj(totalNodes);

        V capacity(
            totalNodes,
            vector<ll>(totalNodes, 0));

        // Source to every mouse
        for (ll i = 0; i < miceCount; i++)
        {
            ll mouseNode = i + 1;

            addEdge(
                source,
                mouseNode,
                1,
                adj,
                capacity);
        }

        // Every hole to sink
        for (ll j = 0; j < holeCount; j++)
        {
            ll holeNode =
                miceCount + j + 1;

            addEdge(
                holeNode,
                sink,
                holes[j].capacity,
                adj,
                capacity);
        }

        // Mouse to reachable holes
        for (ll i = 0; i < miceCount; i++)
        {
            for (ll j = 0; j < holeCount; j++)
            {
                if (canReach(
                        mice[i],
                        holes[j],
                        radius))
                {
                    ll mouseNode = i + 1;

                    ll holeNode =
                        miceCount + j + 1;

                    addEdge(
                        mouseNode,
                        holeNode,
                        1,
                        adj,
                        capacity);
                }
            }
        }

        ll answer =
            edmondsKarp(
                totalNodes,
                source,
                sink,
                adj,
                capacity);

        cout << "Case "
             << cs
             << ": "
             << answer
             << tata;
    }

    return 0;
}
