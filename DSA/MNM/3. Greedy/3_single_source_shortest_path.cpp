#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n = 5; // number of nodes

    vector<vector<int>> adj(n);

    // graph (unweighted)
    adj[0] = {1, 2};
    adj[1] = {0, 3};
    adj[2] = {0, 3};
    adj[3] = {1, 2, 4};
    adj[4] = {3};

    int src = 0;

    vector<int> dist(n, -1); // distance from source
    queue<int> q;

    dist[src] = 0;
    q.push(src);

    while (!q.empty())
    {
        int u = q.front(); // u=1
        q.pop();           // q=2

        for (int v : adj[u])
        {
            if (dist[v] == -1)
            {
                dist[v] = dist[u] + 1; // dist[1]=1, dist[2]=1, dist[3]=2
                q.push(v);             // q=2,3
            }
        }
    }

    // print shortest distances
    for (int i = 0; i < n; i++)
        cout << "dist[" << i << "] = " << dist[i] << endl;

    return 0;
}

/*
Key Notes:

1. Used for unweighted graphs.

2. Shortest path = minimum number of edges.

3. Uses BFS (queue).

4. dist[v] = dist[u] + 1

5. Time Complexity:
   O(V + E)

6. Works because:
   BFS explores level by level → shortest path first.

7. No negative weight issue here.
*/