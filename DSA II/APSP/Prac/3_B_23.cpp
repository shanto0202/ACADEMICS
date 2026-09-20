#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"

const ll INF = 4e18;

// ---------- Floyd-Warshall ----------
void floydWarshall(ll n, vector<vector<ll>> &dist)
{
    for (ll k = 0; k < n; k++)
    {
        for (ll i = 0; i < n; i++)
        {
            for (ll j = 0; j < n; j++)
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

    ll n, m;
    cin >> n >> m;

    vector<vector<ll>> dist(n, vector<ll>(n, INF));

    for (ll i = 0; i < n; i++)
    {
        dist[i][i] = 0;
    }

    for (ll i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
    }

    ll Y, Z;
    cin >> Y >> Z;

    floydWarshall(n, dist);

    ll q;
    cin >> q;

    while (q--)
    {
        ll source, destination;
        cin >> source >> destination;

        ll throughY = INF;
        ll throughZ = INF;

        if (dist[source][Y] != INF &&
            dist[Y][destination] != INF)
        {
            throughY = dist[source][Y] + dist[Y][destination];
        }

        if (dist[source][Z] != INF && dist[Z][destination] != INF)
        {
            throughZ = dist[source][Z] + dist[Z][destination];
        }

        ll answer = min(throughY, throughZ);

        if (answer == INF)
        {
            cout << -1 << tata;
        }
        else
        {
            cout << answer << tata;
        }
    }

    return 0;
}