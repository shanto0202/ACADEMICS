#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define jora(p, n) pair<ll, ll> p(n)
#define sajai(x) sort(x.begin(), x.end())
#define arr(v, x, y) vector<vector<ll>> v(x, vector<int>(y))
#define loop(i, j, n) for (ll i = j; i < n; i++)
#define in(v) loop(i, 0, v.size()) cin >> v[i]
#define out(v) loop(i, 0, v.size()) cout << v[i] << " "
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define tata "\n"
using namespace std;

void dfs(vector<vector<ll>> &given, vector<bool> &dekhsi, ll j, vector<ll> &pelam)
{
    dekhsi[j] = true;
    pelam.pb(j);
    loop(i, 0, given[j].size())
    {
        if (!dekhsi[given[j][i]])
        {
            dfs(given, dekhsi, given[j][i], pelam);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    bool x = true;
    ll n;
    if (cin >> n)
    {
        vector<vector<ll>> v(n), v1;
        string s;
        getline(cin, s);
        while (getline(cin, s))
        {
            if (s.size() == 0)
            {
                break;
            }
            ll a1, a2;
            char ch;
            stringstream ss(s);
            ss >> ch >> a1 >> ch >> a2 >> ch;
            v[a1].pb(a2);
            v[a2].pb(a1);
        }
        vector<bool> seen(n, false);
        loop(i, 0, n)
        {
            if (!seen[i])
            {
                vector<ll> emni;
                dfs(v, seen, i, emni);
                sajai(emni);
                v1.pb(emni);
            }
        }
        if (!x)
        {
            cout << tata;
        }
        x = false;
        cout << v1.size() << tata;
        loop(i, 0, v1.size())
        {
            cout << "Group " << i + 1 << ": {";
            loop(j, 0, v1[i].size())
            {
                cout << v1[i][j] << ((j + 1 == v1[i].size()) ? "} | " : ", ");
            }
            vector<vector<ll>> ye;
            loop(a, 0, v1[i].size())
            {
                loop(b, a + 1, v1[i].size())
                {
                    ll u = v1[i][a], w = v1[i][b], flag = 0;
                    loop(k, 0, v[u].size())
                    {
                        if (v[u][k] == w)
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if (!flag)
                    {
                        ye.pb({u, w});
                    }
                }
            }
            if (ye.empty())
            {
                cout << "none";
            }
            else
            {
                loop(r, 0, ye.size())
                {
                    cout << "[" << ye[r][0] << "," << ye[r][1] << "]";
                    if (r + 1 != ye.size())
                    {
                        cout << ", ";
                    }
                }
            }
            cout << tata;
        }
    }
    return 0;
}