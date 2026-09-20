
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define tata "\n"
#define V vector<vector<ll>>
#define loop(i, j, n) for (ll i = j; i < n; i++)

// Checks all connected components using BFS coloring.
bool isBipartite(ll n, V &adj)
{
    // 0 = uncolored, 1 and -1 = two partitions
    vector<ll> color(n, 0);

    loop(start, 0, n)
    {
        if (color[start] != 0)
        {
            continue;
        }

        queue<ll> q;
        q.push(start);
        color[start] = 1;

        while (!q.empty())
        {
            ll node = q.front();
            q.pop();

            for (ll child : adj[node])
            {
                if (color[child] == 0)
                {
                    color[child] = -color[node];
                    q.push(child);
                }
                else if (color[child] == color[node])
                {
                    return false;
                }
            }
        }
    }

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    V adj(n);

    loop(i, 0, m)
    {
        ll u, v;
        cin >> u >> v;

        adj[u].pb(v);
        adj[v].pb(u);
    }

    if (isBipartite(n, adj))
    {
        cout << "YES" << tata;
    }
    else
    {
        cout << "NO" << tata;
    }

    return 0;
}
