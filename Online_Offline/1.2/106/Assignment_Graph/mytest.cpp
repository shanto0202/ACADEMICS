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
    ll t;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        vector<vector<ll>> v(n), v1;
        loop(i, 0, n)
        {
            ll a1, a2;
            cin >> a1 >> a2;
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
                v1.pb(emni);
            }
        }
        cout << v1.size() << tata;
        loop(i, 0, v1.size())
        {
            cout << "Group " << i + 1 << ": {";
            loop(j, 0, v1[i].size())
            {
                cout << v1[i][j] << ((j == v1[i].size() - 1) ? "} | " : ", ");
            }
            loop(j, 0, v1[i].size())
            {
                vector<ll> phi;
                phi = v1[i];
                loop(l, 0, v[v1[i][j]].size())
                {
                    vector<vector<ll>> ye;
                    loop(g, 0, phi.size())
                    {
                        if (v[v1[i][j]][l] == phi[g] && g != v1[i][j])
                        {
                            phi.erase(phi.begin() + g);
                        }
                        if (phi[g] == v1[i][j])
                        {
                            phi.erase(phi.begin() + g);
                        }
                    }
                    loop(w, 0, phi.size())
                    {
                        ye.pb({v1[i][j], phi[w]});
                    }
                    loop(r, 0, ye.size())
                    {
                        cout << "[" << ye[r][0] << "," << ye[r][1] << ((r == ye.size() - 1) ? "]" : "], ");
                    }
                }
            }
            cout << tata;
        }
    }
    return 0;
}