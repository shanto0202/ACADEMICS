#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define tata "\n"

const int INF = 1e9;

// ---------- Edge Structure ----------
struct Edge
{
    int u, v, w;
};
// ---------- Bellman-Ford for Negative Edge Weighted Graph ----------
void bellmanFord(int n, vector<Edge> &edges, int source, vector<int> &dist, int k)
{
    dist.assign(n + 1, INF);
    dist[source] = 0;
    for (int i = 0; i <= k; i++)
    {
        vector<int> nextDist = dist;
        bool changed = false;
        for (Edge e : edges)
        {
            if (dist[e.u] != INF && nextDist[e.v] > dist[e.u] + e.w)
            {
                nextDist[e.v] = dist[e.u] + e.w;
                changed = true;
            }
        }
        dist = nextDist;
        if (!changed)
        {
            break;
        }
    }
}

class Solution
{
public:
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
    {
        int m = flights.size();
        vector<Edge> edges;
        for (int i = 0; i < m; i++)
        {
            edges.pb({flights[i][0], flights[i][1], flights[i][2]}); // directed edge
        }
        vector<int> dist;
        bellmanFord(n, edges, src, dist, k);
        if (dist[dst] == INF)
        {
            return -1;
        }
        else
        {
            return dist[dst];
        }
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, src, dst, k;
    cin >> n >> m >> src >> dst >> k;
    vector<vector<int>> v(m, vector<int>(3));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> v[i][j];
        }
    }
    Solution sol;
    cout << sol.findCheapestPrice(n, v, src, dst, k) << tata;
    return 0;
}