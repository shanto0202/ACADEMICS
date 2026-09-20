// https://leetcode.com/problems/evaluate-division/

/*
Input:
testCase
For each test case:
m q
m equations: a b value    means a / b = value
q queries: a b
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"

// ---------- Multiplicative Floyd-Warshall ----------
void floydWarshall(ll n, vector<vector<long double>> &ratio)
{
    for (ll k = 0; k < n; k++)
    {
        for (ll i = 0; i < n; i++)
        {
            for (ll j = 0; j < n; j++)
            {
                if (ratio[i][k] == 0 || ratio[k][j] == 0)
                {
                    continue;
                }
                ratio[i][j] = ratio[i][k] * ratio[k][j];
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
        ll m, q;
        cin >> m >> q;

        vector<tuple<string, string, long double>> equations;
        unordered_map<string, ll> id;

        for (ll i = 0; i < m; i++)
        {
            string a, b;
            long double value;

            cin >> a >> b >> value;

            equations.pb({a, b, value});

            if (!id.count(a))
            {
                id[a] = id.size();
            }

            if (!id.count(b))
            {
                id[b] = id.size();
            }
        }

        ll n = id.size();

        vector<vector<long double>> ratio(
            n, vector<long double>(n, 0));

        for (ll i = 0; i < n; i++)
        {
            ratio[i][i] = 1;
        }

        for (auto equation : equations)
        {
            string a, b;
            long double value;

            tie(a, b, value) = equation;

            ll u = id[a];
            ll v = id[b];

            ratio[u][v] = value;
            ratio[v][u] = 1.0 / value;
        }

        floydWarshall(n, ratio);

        cout << fixed << setprecision(5);

        while (q--)
        {
            string a, b;
            cin >> a >> b;

            if (!id.count(a) || !id.count(b))
            {
                cout << -1.00000 << tata;
                continue;
            }

            ll u = id[a];
            ll v = id[b];

            if (ratio[u][v] == 0)
            {
                cout << -1.00000 << tata;
            }
            else
            {
                cout << ratio[u][v] << tata;
            }
        }
    }

    return 0;
}