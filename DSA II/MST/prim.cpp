#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, long long>>> adj(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<bool> visited(n + 1, false);

    // {weight, node}
    priority_queue<pair<long long, int>,vector<pair<long long, int>>,greater<pair<long long, int>>>pq;

    int start = 1;
    pq.push({0, start});

    long long mstCost = 0;
    int takenNodes = 0;

    while (!pq.empty())
    {
        auto [cost, u] = pq.top();
        pq.pop();

        if (visited[u])
            continue;

        visited[u] = true;
        mstCost += cost;
        takenNodes++;

        for (auto [v, w] : adj[u])
        {
            if (!visited[v])
            {
                pq.push({w, v});
            }
        }
    }

    if (takenNodes != n)
    {
        cout << "Graph is not connected\n";
        return 0;
    }

    cout << "MST Cost: " << mstCost << '\n';

    return 0;
}