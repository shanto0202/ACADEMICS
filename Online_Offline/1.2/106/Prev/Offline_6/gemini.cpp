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

ll n, m,vt = 0;
double mot_cost = 0;
vector<pair<pair<double, ll>, double>> cities;
vector<pair<ll, ll>> edges_2;
vector<vector<ll>> adj;
vector<ll> vis;

// DFS to check if 'u' and 'target' are already connected
bool dfs(ll u, ll t)
{
    if (u == t)
    {
        return true;
    }
    vis[u] = vt;
    loop(i, 0, adj[u].size())
    {
        ll v = adj[u][i];
        if (vis[v] != vt)
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
    ll count = r - l + 1;
    // Base Case
    if (count <= m)
    {
        vector<pair<double, pair<ll, pair<ll, ll>>>> edges;
        loop(i, l, r + 1)
        {
            loop(j, i + 1, r + 1)
            {
                // cities[i].first.first is X, cities[i].second is Y, cities[i].first.second is ID
                double d = ds(cities[i].first.first, cities[i].second, cities[j].first.first, cities[j].second);
                ll u = cities[i].first.second;
                ll v = cities[j].first.second;
                edges.pb({d, {abs(u - v), {u, v}}});
            }
        }
        sajai(edges);
        loop(i, 0, edges.size())
        {
            double cost = edges[i].first;
            ll u = edges[i].second.second.first;
            ll v = edges[i].second.second.second;
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
    double min_dist = LONG_LONG_MAX;
    ll best_u = -1, best_v = -1;
    ll left_start = max(l, mid - m + 1);
    ll right_end = min(r, mid + m);
    loop(i, left_start, mid + 1)
    {
        loop(j, mid + 1, right_end + 1)
        {
            double d = ds(cities[i].first.first, cities[i].second, cities[j].first.first, cities[j].second);
            if (d < min_dist)
            {
                min_dist = d;
                best_u = cities[i].first.second;
                best_v = cities[j].first.second;
            }
        }
    }
    if (best_u != -1 && best_v != -1)
    {
        mot_cost += min_dist;
        edges_2.pb({best_u, best_v});
        adj[best_u].pb(best_v);
        adj[best_v].pb(best_u);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    cities.resize(n);
    adj.resize(n + 1);
    vis.resize(n + 1, 0);
    loop(i, 0, n)
    {
        ll id;
        double x, y;
        cin >> id >> x >> y;
        cities[i] = {{x, id}, y};
    }
    sajai(cities);
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