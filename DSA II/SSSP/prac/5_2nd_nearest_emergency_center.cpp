#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define tata "\n"

const ll INF = 4e18;

// 4. Second nearest emergency center
bool addState(ll node, ll center, ll newDist, vector<array<ll, 2>> &dist, vector<array<ll, 2>> &owner)
{
    ll oldDist = INF;
    for (ll i = 0; i < 2; i++)
    {
        if (owner[node][i] == center)
            oldDist = dist[node][i];
    }

    if (newDist >= oldDist)
        return false;

    vector<pair<ll, ll>> candidates;

    for (ll i = 0; i < 2; i++)
    {
        if (owner[node][i] != -1 && owner[node][i] != center)
        {
            candidates.pb({dist[node][i], owner[node][i]});
        }
    }

    candidates.pb({newDist, center});
    sort(candidates.begin(), candidates.end());

    dist[node] = {INF, INF};
    owner[node] = {-1, -1};

    for (ll i = 0; i < min(2LL, (ll)candidates.size()); i++)
    {
        dist[node][i] = candidates[i].first;
        owner[node][i] = candidates[i].second;
    }

    for (ll i = 0; i < 2; i++)
    {
        if (owner[node][i] == center && dist[node][i] == newDist)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, k;
    cin >> n >> m >> k;

    vector<ll> centers(k);

    for (ll &center : centers)
        cin >> center;

    vector<vector<pair<ll, ll>>> reverseAdj(n + 1);

    for (ll i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        reverseAdj[v].pb({u, w});
    }

    vector<array<ll, 2>> dist(n + 1);
    vector<array<ll, 2>> owner(n + 1);

    for (ll node = 1; node <= n; node++)
    {
        dist[node] = {INF, INF};
        owner[node] = {-1, -1};
    }

    // {distance, node, sourceCenter}
    priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<tuple<ll, ll, ll>>> pq;

    for (ll center : centers)
    {
        if (addState(center, center, 0, dist, owner))
            pq.push({0, center, center});
    }

    while (!pq.empty())
    {
        auto [currentDist, node, center] = pq.top();
        pq.pop();

        bool valid = false;

        for (ll i = 0; i < 2; i++)
        {
            if (owner[node][i] == center &&
                dist[node][i] == currentDist)
            {
                valid = true;
            }
        }

        if (!valid)
            continue;

        for (auto [nextNode, weight] : reverseAdj[node])
        {
            ll newDist = currentDist + weight;

            if (addState(nextNode, center, newDist, dist, owner))
            {
                pq.push({newDist, nextNode, center});
            }
        }
    }

    for (ll node = 1; node <= n; node++)
    {
        if (dist[node][1] == INF)
            cout << -1 << tata;
        else
            cout << dist[node][1] << tata;
    }

    return 0;
}