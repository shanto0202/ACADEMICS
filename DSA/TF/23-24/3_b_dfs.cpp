#include <bits/stdc++.h>
using namespace std;

vector<int> adj[100];

int color[100]; // 0=WHITE, 1=GRAY, 2=BLACK
int parent[100];
int disc[100], fin[100];
int timer = 0;

void iterativeDFS(int src)
{
    stack<int> st;
    st.push(src);
    parent[src] = -1;

    while (!st.empty())
    {
        int u = st.top();

        // first time visit
        if (color[u] == 0)
        {
            color[u] = 1; // GRAY
            disc[u] = ++timer;
        }

        bool pushed = false;

        for (int v : adj[u])
        {
            if (color[v] == 0)
            {
                cout << "Tree Edge: " << u << " -> " << v << endl;
                parent[v] = u;
                st.push(v);
                pushed = true;
                break;
            }
            else if (color[v] == 1)
            {
                cout << "Back Edge: " << u << " -> " << v << endl;
            }
            else // color[v] == BLACK
            {
                // distinguish forward vs cross
                if (disc[u] < disc[v])
                    cout << "Forward Edge: " << u << " -> " << v << endl;
                else
                    cout << "Cross Edge: " << u << " -> " << v << endl;
            }
        }

        if (!pushed)
        {
            color[u] = 2; // BLACK
            fin[u] = ++timer;
            st.pop();
        }
    }
}

int main()
{
    /*
        r=0, s=1, t=2, u=3, v=4, w=5, x=6, y=7
    */

    adj[1] = {0, 5}; // s -> r, w
    adj[0] = {4};    // r -> v
    adj[2] = {5};    // t -> w
    adj[3] = {2, 6}; // u -> t, x
    adj[5] = {6};    // w -> x
    adj[6] = {2};    // x -> t
    adj[7] = {3, 6}; // y -> u, x

    for (int i = 0; i < 8; i++)
    {
        color[i] = 0;
        parent[i] = -1;
    }

    iterativeDFS(1); // start from s

    return 0;
}

/*
Key Notes:

1. Tree Edge:
   WHITE → first discovery

2. Back Edge:
   GRAY → ancestor

3. Forward Edge:
   BLACK and disc[u] < disc[v]
   (u → descendant)

4. Cross Edge:
   BLACK and disc[u] > disc[v]
   (different subtree)

5. Time Complexity:
   O(V + E)

6. Important:
   Without disc[], you CANNOT distinguish forward vs cross edge.
*/