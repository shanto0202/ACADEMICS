#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define tata "\n"

const ll INF = 4e18;

// ---------- Floyd-Warshall ----------
void floydWarshall(ll n, vector<vector<ll>> &dist)
{
    for (ll k = 0; k <= n; k++)
    {
        for (ll i = 0; i <= n; i++)
        {
            for (ll j = 0; j <= n; j++)
            {
                if (dist[i][k] == INF || dist[k][j] == INF)
                {
                    continue;
                }
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, A, B, q;
    cin >> n >> m;

    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, INF));

    for (ll i = 0; i <= n; i++)
    {
        dist[i][i] = 0;
    }

    for (ll i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        // Directed edge
        dist[u][v] = min(dist[u][v], w);
    }

    cin >> A >> B;
    floydWarshall(n, dist);
    cin >> q;

    while (q--)
    {
        ll s, d;
        cin >> s >> d;

        ll throughA = INF, throughB = INF;

        if (dist[s][A] != INF && dist[A][d] != INF)
        {
            throughA = dist[s][A] + dist[A][d];
        }

        if (dist[s][B] != INF && dist[B][d] != INF)
        {
            throughB = dist[s][B] + dist[B][d];
        }

        if (throughA == INF && throughB == INF)
        {
            cout << -1 << tata;
        }
        else if (throughA < throughB)
        {
            cout << throughA << " " << A << tata;
        }
        else if (throughB < throughA)
        {
            cout << throughB << " " << B << tata;
        }
        else
        {
            // Equal distance: smaller hub number
            cout << throughA << " " << min(A, B) << tata;
        }
    }

    return 0;
}