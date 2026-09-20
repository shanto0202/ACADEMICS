// https://www.geeksforgeeks.org/dsa/minimize-count-of-connections-required-to-be-rearranged-to-make-all-the-computers-connected/
#include <bits/stdc++.h>
using namespace std;

class DSU
{
public:
    vector<int> parent, sz;

    DSU(int n)
    {
        parent.resize(n);
        sz.assign(n, 1);

        for (int i = 0; i < n; i++)
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
            return false;

        if (sz[a] < sz[b])
            swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];

        return true;
    }
};

int makeConnected(int n, vector<vector<int>> &connections)
{
    int m = connections.size();

    // Minimum edges needed to connect n nodes = n - 1
    if (m < n - 1)
        return -1;

    DSU dsu(n);

    for (auto edge : connections)
    {
        int u = edge[0];
        int v = edge[1];

        dsu.unite(u, v);
    }

    int components = 0;

    for (int i = 0; i < n; i++)
    {
        if (dsu.find(i) == i)
        {
            components++;
        }
    }

    return components - 1;
}

int main()
{
    int n = 4;
    vector<vector<int>> connections = {
        {0, 1},
        {0, 2},
        {1, 2}};

    cout << makeConnected(n, connections) << '\n';

    return 0;
}