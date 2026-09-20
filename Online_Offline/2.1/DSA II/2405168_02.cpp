#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"
#define V vector<vector<ll>>
#define loop(i, j, n) for (ll i = j; i < n; i++)
const ll INF = LLONG_MAX;

struct Flight
{
    string s, dep, arr;
    ll dept, arrt;
};

ll somoy_dekhao(string s)
{
    ll a = s[0] - '0';
    ll b = s[1] - '0';
    ll c = s[3] - '0';
    ll d = s[4] - '0';
    return (a * 10 + b) * 60 + c * 10 + d;
}

ll bfs(ll source, ll sink, V &adj, V &capacity, vector<ll> &parent)
{
    fill(parent.begin(), parent.end(), -1);
    parent[source] = -2;
    queue<pair<ll, ll>> q;
    q.push({source, INF});
    while (!q.empty())
    {
        ll node = q.front().first;
        ll flow = q.front().second;
        q.pop();

        for (ll child : adj[node])
        {
            if (parent[child] == -1 && capacity[node][child] > 0)
            {
                parent[child] = node;
                ll newFlow = min(flow, capacity[node][child]);
                if (child == sink)
                {
                    return newFlow;
                }
                q.push({child, newFlow});
            }
        }
    }
    return 0;
}

ll edmondsKarp(ll n, ll source, ll sink, V &adj, V &capacity)
{
    ll maxFlow = 0;
    vector<ll> parent(n + 1);
    while (true)
    {
        ll pathFlow = bfs(source, sink, adj, capacity, parent);
        if (pathFlow == 0)
        {
            break;
        }
        maxFlow += pathFlow;
        ll node = sink;
        while (node != source)
        {
            ll previous = parent[node];
            capacity[previous][node] -= pathFlow;
            capacity[node][previous] += pathFlow;
            node = previous;
        }
    }
    return maxFlow;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, source = 0, a = 1;
    cin >> n;
    ll sink = 2 * n + 1, N = 2 * n + 2;
    V adj(N), capacity(N, vector<ll>(N, 0));
    vector<Flight> fl(n);
    vector<ll> nF(n, -1), pF(n, -1);

    loop(i, 0, n)
    {
        string s, dep, arr, dept, arrt;
        cin >> s >> dep >> arr >> dept >> arrt;
        fl[i].s = s;
        fl[i].dep = dep;
        fl[i].arr = arr;
        fl[i].dept = somoy_dekhao(dept);
        fl[i].arrt = somoy_dekhao(arrt);
    }
    loop(i, 0, n)
    {
        ll l = i + 1, r = n + i + 1;
        adj[source].pb(l);
        adj[l].pb(source);
        capacity[source][l] = 1;
        adj[r].pb(sink);
        adj[sink].pb(r);
        capacity[r][sink] = 1;
    }
    loop(i, 0, n)
    {
        loop(j, 0, n)
        {
            if (i == j)
            {
                continue;
            }
            if (fl[i].arr == fl[j].dep && fl[i].arrt + 180 <= fl[j].dept)
            {
                ll l = i + 1, r = n + j + 1;
                adj[l].pb(r);
                adj[r].pb(l);
                capacity[l][r] = 1;
            }
        }
    }
    ll maxMatching = edmondsKarp(N, source, sink, adj, capacity);
    cout << "Number of Aircraft: " << n-maxMatching << tata;
    loop(i, 0, n)
    {
        loop(j, 0, n)
        {
            if (i == j)
            {
                continue;
            }
            if (fl[i].arr == fl[j].dep && fl[i].arrt + 180 <= fl[j].dept)
            {
                ll l = i + 1, r = n + j + 1;
                if (capacity[l][r] == 0)
                {
                    nF[i] = j;
                    pF[j] = i;
                }
            }
        }
    }
    loop(i, 0, n)
    {
        if (pF[i] == -1)
        {
            cout << "Aircraft " << a << ": ";

            ll temp = i;
            while (temp != -1)
            {
                cout << fl[temp].s;
                if (nF[temp] != -1)
                {
                    cout << " -> ";
                }
                temp = nF[temp];
            }
            cout << tata;
            a++;
        }
    }
    return 0;
}