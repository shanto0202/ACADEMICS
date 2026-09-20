// https://leetcode.com/problems/course-schedule-iv/

/*
Input:
testCase
For each test case:
n m q
m prerequisite edges: u v
q queries: u v
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"

// ---------- Boolean Floyd-Warshall ----------
void floydWarshall(ll n, vector<vector<ll>> &reach)
{
    for (ll k = 0; k < n; k++)
    {
        for (ll i = 0; i < n; i++)
        {
            for (ll j = 0; j < n; j++)
            {
                reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
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
        ll n, m, q;
        cin >> n >> m >> q;

        vector<vector<ll>> reach(n, vector<ll>(n, 0));

        for (ll i = 0; i < m; i++)
        {
            ll u, v;
            cin >> u >> v;

            reach[u][v] = 1;
        }

        floydWarshall(n, reach);

        while (q--)
        {
            ll u, v;
            cin >> u >> v;

            if (reach[u][v])
            {
                cout << "true" << tata;
            }
            else
            {
                cout << "false" << tata;
            }
        }
    }

    return 0;
}