#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"
#define vr(v, x) vector<ll> v(x)
#define vrr(v, x, y) vector<vector<ll>> v(x, vector<ll>(y))
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

ll n, m, vt = 0;
double mot_cost = 0;
vector<pair<pair<double, ll>, double>> elaka;
vector<pair<ll, ll>> edges_2;
vector<vector<ll>> adj;
vector<ll> dekhsi;

bool dfs(ll u, ll t)
{
    if (u == t)
    {
        return true;
    }
    dekhsi[u] = vt;
    loop(i, 0, adj[u].size())
    {
        ll v = adj[u][i];
        if (dekhsi[v] != vt)
        {
            if (dfs(v, t))
            {
                return true;
            }
        }
    }
    return false;
}

double ds(double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void solve(ll l, ll r)
{
    ll c = r - l + 1;
    // Base Case
    if (c <= m)
    {
        vector<pair<double, pair<ll, pair<ll, ll>>>> edges;
        loop(i, l, r + 1)
        {
            loop(j, i + 1, r + 1)
            {
                double d = ds(elaka[i].first.first, elaka[i].second, elaka[j].first.first, elaka[j].second);
                ll u = elaka[i].first.second, v = elaka[j].first.second;
                edges.pb({d, {abs(u - v), {u, v}}});
            }
        }
        sajai(edges);
        loop(i, 0, edges.size())
        {
            double cost = edges[i].first;
            ll u = edges[i].second.second.first, v = edges[i].second.second.second;
            vt++;
            if (!dfs(u, v))
            {
                adj[u].pb(v);
                adj[v].pb(u);
                mot_cost += cost;
                edges_2.pb({u, v});
            }
        }
        return;
    }
    // Divide
    ll mid = l + (r - l) / 2;
    solve(l, mid);
    solve(mid + 1, r);
    // Merge
    double min_ds = LONG_LONG_MAX;
    ll u1 = -1, v1 = -1;
    ll ls = max(l, mid - m + 1);
    ll re = min(r, mid + m);
    loop(i, ls, mid + 1)
    {
        loop(j, mid + 1, re + 1)
        {
            double d = ds(elaka[i].first.first, elaka[i].second, elaka[j].first.first, elaka[j].second);
            if (d < min_ds)
            {
                min_ds = d;
                u1 = elaka[i].first.second;
                v1 = elaka[j].first.second;
            }
        }
    }
    if (u1 != -1 && v1 != -1)
    {
        mot_cost += min_ds;
        edges_2.pb({u1, v1});
        adj[u1].pb(v1);
        adj[v1].pb(u1);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    elaka.resize(n);
    adj.resize(n + 1);
    dekhsi.resize(n + 1, 0);
    loop(i, 0, n)
    {
        ll id;
        double x, y;
        cin >> id >> x >> y;
        elaka[i] = {{x, id}, y};
    }
    sajai(elaka);
    solve(0, n - 1);
    cout << fixed << setprecision(2);
    cout << "Total Cost: " << mot_cost << tata;
    cout << "Edges:\n";
    loop(i, 0, edges_2.size())
    {
        cout << edges_2[i].first << " " << edges_2[i].second << tata;
    }
    return 0;
}