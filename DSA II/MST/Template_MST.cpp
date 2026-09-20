#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"
#define vr(v, x) vector<ll> v(x)
#define vrr(v, x, y) vector<vector<ll>> v(x, vector<ll>(y))
#define sajai(x) sort(x.begin(), x.end())
#define rsort(a) sort(a.begin(), a.end(), greater<>())
#define ulta(a) reverse(a.begin(), a.end())
#define mucho(a, j) a.erase(a.begin() + j)
#define choto(a) *min_element(a.begin(), a.end())
#define boro(a) *max_element(a.begin(), a.end())
#define jog(a) accumulate(a.begin(), a.end(), 0LL)
#define bit(n) __builtin_popcountll(n)
#define loop(i, j, n) for (ll i = j; i < n; i++)
#define in(v) loop(i, 0, v.size()) cin >> v[i]
#define out(v) loop(i, 0, v.size()) cout << v[i] << " "

struct Edge
{
    ll u, v, w;
};

bool cmp(Edge a, Edge b)
{
    return a.w < b.w;
}

// ---------- DFS/BFS Part ----------
vector<vector<ll>> adj;
vector<ll> visited;

void dfs(ll node)
{
    visited[node] = 1;

    for (ll child : adj[node])
    {
        if (!visited[child])
        {
            dfs(child);
        }
    }
}

void bfs(ll start)
{
    queue<ll> q;
    q.push(start);
    visited[start] = 1;

    while (!q.empty())
    {
        ll node = q.front();
        q.pop();

        for (ll child : adj[node])
        {
            if (!visited[child])
            {
                visited[child] = 1;
                q.push(child);
            }
        }
    }
}
// ---------- DFS/BFS Part End ----------

class DSU
{
public:
    vector<ll> parent, sz;

    DSU(ll n)
    {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);

        for (ll i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    ll find(ll x)
    {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    bool unite(ll a, ll b)
    {
        a = find(a);
        b = find(b);

        if (a == b)
        {
            return false;
        }

        if (sz[a] < sz[b])
        {
            swap(a, b);
        }

        parent[b] = a;
        sz[a] += sz[b];

        return true;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, u, v, w, ans = 0, edgeCount = 0;
    cin >> n >> m;

    vector<Edge> edges;

    adj.resize(n + 1);
    visited.assign(n + 1, 0);

    for (ll i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        edges.pb({u, v, w});

        // For DFS/BFS graph traversal
        adj[u].pb(v);
        adj[v].pb(u);
    }

    // Example use of DFS/BFS if needed:
    // dfs(1);
    // bfs(1);

    sort(edges.begin(), edges.end(), cmp);

    DSU dsu(n);

    for (Edge e : edges)
    {
        if (dsu.unite(e.u, e.v))
        {
            ans += e.w;
            edgeCount++;

            if (edgeCount == n - 1)
            {
                break;
            }
        }
    }

    if (edgeCount == n - 1)
    {
        cout << ans << tata;
    }
    else
    {
        cout << "IMPOSSIBLE" << tata;
    }

    return 0;
}