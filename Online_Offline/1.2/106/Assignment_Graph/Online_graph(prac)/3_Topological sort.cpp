#include <bits/stdc++.h>
using namespace std;

vector<int> topoSort(int V, vector<int> adj[]) {
    vector<int> indeg(V,0);

    for(int i=0;i<V;i++)
        for(int v:adj[i]) indeg[v]++;

    queue<int> q;
    for(int i=0;i<V;i++)
        if(indeg[i]==0) q.push(i);

    vector<int> topo;

    while(!q.empty()){
        int u=q.front(); q.pop();
        topo.push_back(u);

        for(int v:adj[u]){
            if(--indeg[v]==0) q.push(v);
        }
    }
    return topo;
}

int main() {
    int V = 6;
    vector<int> adj[V];

    adj[5] = {2,0};
    adj[4] = {0,1};
    adj[2] = {3};
    adj[3] = {1};

    vector<int> ans = topoSort(V, adj);

    for(int x: ans) cout << x << " ";
}

/*
PROBLEM:

Given a Directed Acyclic Graph (DAG),
return any valid topological ordering of vertices.

A topological sort is a linear ordering such that
for every directed edge u -> v, u comes before v.

Example:
Input:
5→2, 5→0
4→0, 4→1
2→3
3→1

Output:
One possible: 5 4 2 3 1 0
*/