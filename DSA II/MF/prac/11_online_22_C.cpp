#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define tata "\n"
#define V vector<vector<ll>>
#define loop(i, j, n) for (ll i = j; i < n; i++)

const ll INF = LLONG_MAX;

struct Person
{
    ll experience;
    ll age;
    ll criminal;
    ll origin;
    ll weapon;
    ll trust;
    ll language;
};

ll bfs(
    ll source,
    ll sink,
    V &adj,
    V &capacity,
    vector<ll> &parent)
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
            if (parent[child] == -1 &&
                capacity[node][child] > 0)
            {
                parent[child] = node;

                ll newFlow =
                    min(flow, capacity[node][child]);

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

ll edmondsKarp(
    ll totalNodes,
    ll source,
    ll sink,
    V &adj,
    V &capacity)
{
    ll maxFlow = 0;
    vector<ll> parent(totalNodes);

    while (true)
    {
        ll pathFlow =
            bfs(
                source,
                sink,
                adj,
                capacity,
                parent);

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

void addEdge(
    ll u,
    ll v,
    ll cap,
    V &adj,
    V &capacity)
{
    adj[u].pb(v);
    adj[v].pb(u);

    capacity[u][v] += cap;
}

bool compatible(
    Person member,
    Person partner)
{
    if (abs(member.experience - partner.experience) > 12)
    {
        return false;
    }

    if (abs(member.age - partner.age) > 5)
    {
        return false;
    }

    if (member.criminal != partner.criminal)
    {
        return false;
    }

    if (member.origin != partner.origin)
    {
        return false;
    }

    if (member.weapon == 0 && partner.weapon == 0)
    {
        return false;
    }

    if (member.trust + partner.trust < 10)
    {
        return false;
    }

    if ((member.language & partner.language) == 0)
    {
        return false;
    }

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll testCases;
    cin >> testCases;

    for (ll cs = 1; cs <= testCases; cs++)
    {
        ll m, n;
        cin >> m >> n;

        vector<Person> members(m);
        vector<Person> partners(n);

        loop(i, 0, m)
        {
            cin >> members[i].experience
                >> members[i].age
                >> members[i].criminal
                >> members[i].origin
                >> members[i].weapon
                >> members[i].trust
                >> members[i].language;
        }

        loop(i, 0, n)
        {
            cin >> partners[i].experience
                >> partners[i].age
                >> partners[i].criminal
                >> partners[i].origin
                >> partners[i].weapon
                >> partners[i].trust
                >> partners[i].language;
        }

        ll source = 0;
        ll sink = m + n + 1;
        ll totalNodes = sink + 1;

        V adj(totalNodes);
        V capacity(
            totalNodes,
            vector<ll>(totalNodes, 0));

        // Source to every gang member
        for (ll i = 0; i < m; i++)
        {
            ll memberNode = i + 1;

            addEdge(
                source,
                memberNode,
                1,
                adj,
                capacity);
        }

        // Every potential partner to sink
        for (ll j = 0; j < n; j++)
        {
            ll partnerNode = m + j + 1;

            addEdge(
                partnerNode,
                sink,
                1,
                adj,
                capacity);
        }

        // Add compatibility edges
        for (ll i = 0; i < m; i++)
        {
            for (ll j = 0; j < n; j++)
            {
                if (compatible(
                        members[i],
                        partners[j]))
                {
                    ll memberNode = i + 1;
                    ll partnerNode = m + j + 1;

                    addEdge(
                        memberNode,
                        partnerNode,
                        1,
                        adj,
                        capacity);
                }
            }
        }

        ll answer =
            edmondsKarp(
                totalNodes,
                source,
                sink,
                adj,
                capacity);

        cout << "Case "
             << cs
             << ": "
             << answer
             << tata;
    }

    return 0;
}
