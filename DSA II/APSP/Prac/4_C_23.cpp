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

    vector<vector<ll>> normalDist(n, vector<ll>(n, INF));
    vector<vector<ll>> discountDist(n, vector<ll>(n, INF));

    for (ll i = 0; i < n; i++)
    {
        normalDist[i][i] = 0;
        discountDist[i][i] = 0;
    }

    for (ll i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;

        // Normal and discounted directed edges
        normalDist[u][v] = min(normalDist[u][v], w);

        discountDist[u][v] = min(discountDist[u][v], w - 1);
    }

    ll V;
    cin >> V;

    floydWarshall(n, normalDist);
    floydWarshall(n, discountDist);

    ll q;
    cin >> q;

    while (q--)
    {
        ll source, destination;
        cin >> source >> destination;

        // Route without passing through V
        ll answer = normalDist[source][destination];

        // Route passing through V gets discount
        if (discountDist[source][V] != INF &&
            discountDist[V][destination] != INF)
        {
            ll throughV = discountDist[source][V] + discountDist[V][destination];
            answer = min(answer, throughV);
        }

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