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
const int table_size = 20011; // Prime and large enough for 10000 words
const int probing_method = 1; // 1 = double hashing, 2 = custom probing
const int C1 = 1, C2 = 3;

class HashTable
{
    vector<pair<string, int>> table;
    vector<int> state; // 0 = empty, 1 = occupied, 2 = deleted
    ll hash1(string key)
    {
        ll hash_value = 5381;
        for (char ch : key)
        {
            hash_value = (hash_value * 33 + ch) % table_size;
        }
        return hash_value;
    }
    ll auxHash(string key)
    {
        ll hash_value = 0;
        for (char ch : key)
        {
            hash_value = (hash_value * 31 + ch) % (table_size - 1);
        }
        return hash_value + 1; // Step can never be zero
    }
    ll getIndex(string key, int i)
    {
        ll h = hash1(key);
        ll step = auxHash(key);

        if (probing_method == 1)
        {
            return (h + i * step) % table_size;
        }
        return (h + C1 * i * step + C2 * 1LL * i * i) % table_size;
    }

public:
    HashTable()
    {
        table.resize(table_size);
        state.assign(table_size, 0);
    }
    bool insert(string key, int value)
    {
        int first_deleted = -1;
        for (int i = 0; i < table_size; i++)
        {
            int index = getIndex(key, i);
            if (state[index] == 1 && table[index].first == key)
            {
                return false;
            }
            if (state[index] == 2 && first_deleted == -1)
            {
                first_deleted = index;
            }
            if (state[index] == 0)
            {
                if (first_deleted != -1)
                {
                    index = first_deleted;
                }
                table[index] = {key, value};
                state[index] = 1;
                return true;
            }
        }
        return false;
    }
    void printProbeSequence(string key)
    {
        for (int i = 0; i < table_size; i++)
        {
            int index = getIndex(key, i);
            if (i > 0)
            {
                cout << " -> ";
            }
            cout << index;
            // Search ends after finding the key or a never-used empty slot.
            if (state[index] == 0 ||
                (state[index] == 1 && table[index].first == key))
            {
                break;
            }
        }
        cout << tata;
    }
};

string randomWord(int length)
{
    string word;
    for (int i = 0; i < length; i++)
    {
        word += char('a' + rand() % 26);
    }
    return word;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    HashTable hash_table;
    int unique_words = 0;
    while (unique_words < 10000)
    {
        string word = randomWord(10);
        if (hash_table.insert(word, unique_words + 1))
        {
            unique_words++;
        }
    }
    int n;
    cin >> n;
    while (n--)
    {
        string key;
        cin >> key;
        hash_table.printProbeSequence(key);
    }
    return 0;
}