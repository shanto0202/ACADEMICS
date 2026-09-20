#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define tata "\n"
#define V vector<vector<ll>>
#define loop(i, j, n) for (ll i = j; i < n; i++)

// Checks whether people can be divided into two groups.
bool possibleBipartition(ll n, V &adj)
{
    // 0 = uncolored
    // 1 and -1 = two different groups
    vector<ll> color(n + 1, 0);

    for (ll start = 1; start <= n; start++)
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

    V adj(n + 1);

    loop(i, 0, m)
    {
        ll u, v;
        cin >> u >> v;

        adj[u].pb(v);
        adj[v].pb(u);
    }

    if (possibleBipartition(n, adj))
    {
        cout << "YES" << tata;
    }
    else
    {
        cout << "NO" << tata;
    }

    return 0;
}
