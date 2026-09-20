#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"
#define vrr(v, x, y) vector<vector<ll>> v(x, vector<ll>(y))
#define sajai(x) sort(x.begin(), x.end())
#define loop(i, j, n) for (ll i = j; i < n; i++)
#define in(v) loop(i, 0, v.size()) cin >> v[i]
#define out(v) loop(i, 0, v.size()) cout << v[i] << " "
#define yes cout << "YES" << tata
#define no cout << "NO" << tata

class HashSet
{
    int table_size;
    vector<list<ll>> table;
    int hashFunction(ll key)
    {
        return (key % table_size + table_size) % table_size;
    }
public:
    HashSet(int size)
    {
        table_size = max(1, size);
        table.resize(table_size);
    }
    bool search(ll key)
    {
        int index = hashFunction(key);
        for (ll value : table[index])
        {
            if (value == key)
            {
                return true;
            }
        }
        return false;
    }
    // Returns false when the key was already present.
    bool insert(ll key)
    {
        if (search(key))
        {
            return false;
        }
        table[hashFunction(key)].pb(key);
        return true;
    }
};
void printVector(string label, vector<ll> &v)
{
    cout << label;
    out(v);
    cout << tata;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n;
    vector<ll> a(n);
    in(a);
    cin >> m;
    vector<ll> b(m);
    in(b);
    int size = 2 * (n + m) + 1;
    HashSet set_a(size), set_b(size);
    vector<ll> a, b;
    // Store only unique values even if duplicate input is given.
    for (ll value : a)
    {
        if (set_a.insert(value))
        {
            a.pb(value);
        }
    }
    for (ll value : b)
    {
        if (set_b.insert(value))
        {
            b.pb(value);
        }
    }
    vector<ll> intersection, set_union, difference;
    for (ll value : a)
    {
        set_union.pb(value);
        if (set_b.search(value))
        {
            intersection.pb(value);
        }
        else
        {
            difference.pb(value);
        }
    }
    for (ll value : b)
    {
        if (!set_a.search(value))
        {
            set_union.pb(value);
        }
    }
    printVector("Intersection: ", intersection);
    printVector("Union: ", set_union);
    printVector("Diff (A-B): ", difference);
    return 0;
}