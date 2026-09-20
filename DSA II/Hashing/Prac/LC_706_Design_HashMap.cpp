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

class MyHashMap
{
    static const int table_size = 1009;
    vector<list<pair<int, int>>> table;

    int hashFunction(int key)
    {
        return key % table_size;
    }

public:
    MyHashMap()
    {
        table.resize(table_size);
    }

    void put(int key, int value)
    {
        int index = hashFunction(key);

        for (auto &item : table[index])
        {
            if (item.first == key)
            {
                item.second = value;
                return;
            }
        }

        table[index].pb({key, value});
    }

    int get(int key)
    {
        int index = hashFunction(key);

        for (auto item : table[index])
        {
            if (item.first == key)
            {
                return item.second;
            }
        }

        return -1;
    }

    void remove(int key)
    {
        int index = hashFunction(key);

        for (auto it = table[index].begin(); it != table[index].end(); it++)
        {
            if (it->first == key)
            {
                table[index].erase(it);
                return;
            }
        }
    }
};
