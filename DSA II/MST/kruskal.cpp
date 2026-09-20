#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int u, v;
    long long w;

    bool operator<(const Edge &other) const
    {
        return w < other.w;
    }
};

class DSU
{
public:
    vector<int> parent, sz;

    DSU(int n)
    {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);

        for (int i = 1; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b)
    {
        a = find(a);
        b = find(b);

        if (a == b)
            return false; // cycle hobe

        if (sz[a] < sz[b])
            swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];

        return true;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;

        edges.push_back({u, v, w});
    }

    sort(edges.begin(), edges.end());

    DSU dsu(n);

    long long mstCost = 0;
    vector<Edge> mstEdges;

    for (Edge e : edges)
    {
        if (dsu.unite(e.u, e.v))
        {
            mstCost += e.w;
            mstEdges.push_back(e);
        }
    }

    if ((int)mstEdges.size() != n - 1)
    {
        cout << "Graph is not connected\n";
        return 0;
    }

    cout << "MST Cost: " << mstCost << '\n';

    cout << "MST Edges:\n";
    for (Edge e : mstEdges)
    {
        cout << e.u << " " << e.v << " " << e.w << '\n';
    }

    return 0;
}