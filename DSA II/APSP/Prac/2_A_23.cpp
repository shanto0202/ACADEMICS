#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"

const long double EPS = 1e-12;

// ---------- Floyd-Warshall for Maximum Exchange Rate ----------
void floydWarshall(ll n, vector<vector<long double>> &rate)
{
    for (ll k = 0; k < n; k++)
    {
        for (ll i = 0; i < n; i++)
        {
            for (ll j = 0; j < n; j++)
            {
                if (rate[i][k] == 0 || rate[k][j] == 0)
                {
                    continue;
                }

                rate[i][j] = max(rate[i][j], rate[i][k] * rate[k][j]);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    vector<string> currency(n);
    unordered_map<string, ll> id;

    for (ll i = 0; i < n; i++)
    {
        cin >> currency[i];
        id[currency[i]] = i;
    }

    vector<vector<long double>> rate(n, vector<long double>(n, 0));

    for (ll i = 0; i < n; i++)
    {
        rate[i][i] = 1;
    }

    ll m;
    cin >> m;

    for (ll i = 0; i < m; i++)
    {
        string from, to;
        long double exchangeRate;

        cin >> from >> exchangeRate >> to;

        ll u = id[from];
        ll v = id[to];

        // Best direct exchange rate
        rate[u][v] = max(rate[u][v], exchangeRate);
    }

    floydWarshall(n, rate);

    bool found = false;

    for (ll i = 0; i < n; i++)
    {
        if (rate[i][i] > 1.0 + EPS)
        {
            cout << currency[i] << tata;
            found = true;
        }
    }

    if (!found)
    {
        cout << "No Arbitrage" << tata;
    }

    return 0;
}