#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> parent;

// Find with path compression
int findSet(int x)
{
    if (parent[x] == x)
        return x;
    return parent[x] = findSet(parent[x]);
}

// Union two sets
void unionSet(int a, int b)
{
    a = findSet(a); // 3
    b = findSet(b); // 4

    if (a != b)
        parent[a] = b;
}

int main()
{
    int n = 5;

    // {weight, {u, v}}
    vector<pair<int, pair<int, int>>> edges = {
        {4, {0, 1}},
        {8, {0, 2}},
        {2, {1, 2}},
        {6, {1, 3}},
        {3, {2, 3}},
        {5, {3, 4}}};

    // Make-Set
    parent.resize(n);
    for (int i = 0; i < n; i++)
        parent[i] = i;

    // Sort edges by weight
    sort(edges.begin(), edges.end());

    int mstCost = 0;
    int cnt = 0;

    for (auto e : edges)
    {
        int w = e.first;         // w=2
        int u = e.second.first;  // u=1
        int v = e.second.second; // v=2

        // If no cycle
        if (findSet(u) != findSet(v))
        {
            cout << u << " - " << v << " : " << w << endl;
            mstCost += w;
            unionSet(u, v);
            cnt++;

            if (cnt == n - 1)
                break;
        }
    }

    cout << "MST cost = " << mstCost;

    return 0;
}

/*
Key Notes:

1. Kruskal's Algorithm (Greedy):
   Always pick smallest weight edge.

2. Steps:
   - Make each node its own set
   - Sort edges by weight
   - Pick edge if it does NOT form cycle

3. Cycle Detection:
   findSet(u) != findSet(v)

4. Union-Find:
   - findSet(x) → finds representative
   - unionSet(a, b) → merges sets

5. Stop after (V - 1) edges.

6. Time Complexity:
   O(E log E)  [sorting dominates]

7. Optimization:
   Path compression makes find fast

8. From your slides:
   - Make-Set(v), Find(x), Union(x,y) are core operations :contentReference[oaicite:0]{index=0}
*/