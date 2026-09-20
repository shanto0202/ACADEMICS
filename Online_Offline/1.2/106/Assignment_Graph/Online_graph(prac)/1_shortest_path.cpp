#include <bits/stdc++.h>
using namespace std;

vector<int> shortestPath(int V, vector<int> adj[], int src) {
    vector<int> dist(V, -1);
    queue<int> q;

    q.push(src);
    dist[src] = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

int main() {
    int V = 6;
    vector<int> adj[V];

    // edges
    adj[0] = {1,2};
    adj[1] = {0,3};
    adj[2] = {0,4};
    adj[3] = {1,5};
    adj[4] = {2,5};
    adj[5] = {3,4};

    int src = 0;

    vector<int> dist = shortestPath(V, adj, src);

    for (int d : dist) cout << d << " ";
}

/*
PROBLEM:

Given an undirected graph with V vertices and adjacency list adj[],
find the shortest distance from a source node to all other nodes.

- Graph is unweighted
- If a node is unreachable, return -1 for that node

Example:

Input:
V = 6
Edges:
0-1, 0-2
1-3
2-4
3-5
4-5

Source = 0

Output:
0 1 1 2 2 3

Explanation:
Shortest path distances from node 0 to all nodes.
*/