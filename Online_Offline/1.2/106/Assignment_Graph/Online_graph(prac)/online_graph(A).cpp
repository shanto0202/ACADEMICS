#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"
#define vr(v, x) vector<ll> v(x)
#define vrr(v, x, y) vector<vector<char>> v(x, vector<char>(y))
#define jora(p, n) pair<ll, ll> p(n)
#define sajai(x) sort(x.begin(), x.end())
#define rsort(a) sort(a.begin(), a.end(), greater<>())
#define ulta(a) reverse(a.begin(), a.end())
#define mucho(a, j) a.erase(a.begin() + j)
#define choto(a) *min_element(a.begin(), a.end())
#define boro(a) *max_element(a.begin(), a.end())
#define jog(a) accumulate(a.begin(), a.end(), 0LL)
#define bit(n) __builtin_popcountll(n)
#define loop(i, j, n) for (ll i = j; i < n; i++)
#define in(v) loop(i, 0, v.size()) cin >> v[i]
#define out(v) loop(i, 0, v.size()) cout << v[i] << " "
#define yes cout << "YES" << tata
#define no cout << "NO" << tata

map<string, vector<string>> adj;
vector<pair<string, ll>> ans;

void dfs(string u, ll gen)
{
    if (adj[u].size() == 1)
    {
        ans.pb({adj[u][0], gen + 1});
    }
    for (auto v : adj[u])
    {
        dfs(v, gen + 1);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    set<string> children, parents;
    loop(i, 0, n)
    {
        string u, v;
        cin >> u >> v;
        adj[u].pb(v);
        parents.insert(u);
        children.insert(v);
    }
    string root = "";
    for (auto p : parents)
    {
        if (children.find(p) == children.end())
        {
            root = p;
            break;
        }
    }
    dfs(root, 1);
    if (ans.empty())
    {
        cout << "None" << tata;
    }
    else
    {
        cout << ans.size() << tata;
        loop(i, 0, ans.size())
        {
            cout << ans[i].first << " " << ans[i].second << tata;
        }
    }
    return 0;
}