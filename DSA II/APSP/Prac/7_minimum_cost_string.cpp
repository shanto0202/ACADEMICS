// https://leetcode.com/problems/minimum-cost-to-convert-string-i/

/*
Input:
testCase
For each test case:
source target
m
m conversion rules: original changed cost
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
        string source, target;
        cin >> source >> target;

        ll m;
        cin >> m;

        const ll alphabetSize = 26;

        vector<vector<ll>> dist(alphabetSize, vector<ll>(alphabetSize, INF));

        for (ll i = 0; i < alphabetSize; i++)
        {
            dist[i][i] = 0;
        }

        for (ll i = 0; i < m; i++)
        {
            char original, changed;
            ll cost;

            cin >> original >> changed >> cost;

            ll u = original - 'a';
            ll v = changed - 'a';

            dist[u][v] = min(dist[u][v], cost);
        }

        floydWarshall(alphabetSize, dist);

        ll answer = 0;
        bool possible = true;

        for (ll i = 0; i < source.size(); i++)
        {
            ll u = source[i] - 'a';
            ll v = target[i] - 'a';

            if (dist[u][v] == INF)
            {
                possible = false;
                break;
            }

            answer += dist[u][v];
        }

        if (!possible)
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