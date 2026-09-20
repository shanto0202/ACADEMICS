// https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/

/*
Input:
testCase
For each test case:
n m distanceThreshold
m undirected edges: u v w
*/

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
                if (dist[i][k] == INF ||
                    dist[k][j] == INF)
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

    ll testCase;
    cin >> testCase;

    while (testCase--)
    {
        ll n, m, distanceThreshold;
        cin >> n >> m >> distanceThreshold;

        vector<vector<ll>> dist(n, vector<ll>(n, INF));

        for (ll i = 0; i < n; i++)
        {
            dist[i][i] = 0;
        }

        for (ll i = 0; i < m; i++)
        {
            ll u, v, w;
            cin >> u >> v >> w;

            // Undirected edge
            dist[u][v] = min(dist[u][v], w);
            dist[v][u] = min(dist[v][u], w);
        }

        floydWarshall(n, dist);

        ll answer = -1;
        ll minimumCount = INF;

        for (ll city = 0; city < n; city++)
        {
            ll count = 0;

            for (ll otherCity = 0; otherCity < n; otherCity++)
            {
                if (city != otherCity &&
                    dist[city][otherCity] <= distanceThreshold)
                {
                    count++;
                }
            }

            // Equal count selects greater city number
            if (count <= minimumCount)
            {
                minimumCount = count;
                answer = city;
            }
        }

        cout << answer << tata;
    }

    return 0;
}