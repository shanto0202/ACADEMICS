#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"
#define loop(i, j, n) for (ll i = j; i < n; i++)
using ull = unsigned long long;
using uc = unsigned char;
const ll size = 13;
const double MAX_LOAD = 0.50;
const double MIN_LOAD = 0.25;
const ll C1 = 1, C2 = 1;
bool isPrime(ll n)
{
    if (n < 2)
    {
        return false;
    }
    for (ll i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }   
    return true;
}
ll porer_prime(ll n)
{
    n++;
    while (!isPrime(n))
    {
        n++;
    }
    return n;
}
ll ager_prime(ll n)
{
    n--;
    while (!isPrime(n))
    {
        n--;
    }
    return n;
}
template <typename Key>
string key_theke_string(const Key &key)
{
    stringstream ss;
    ss << key;
    return ss.str();
}
// DJB2 and SDBM.
ull h1(const string &s)
{
    ull h = 5381;
    for (uc c : s)
    {
        h = h * 33 + c;
    }
    return h;
}
ull h2(const string &s)
{
    ull h = 0;
    for (uc c : s)
    {
        h = c + (h << 6) + (h << 16) - h;
    }
    return h;
}
template <typename Key>
ll pri_hash(const Key &key, int hash_Num, ll sz)
{
    string s = key_theke_string(key);
    return (hash_Num == 1 ? h1(s) : h2(s)) % sz;
}
ull aux_Hash(const string &s, ll sz)
{
    ull h = 0;
    for (uc c : s)
    {
        h = h * 37 + c;
    }
    return 1 + h % (sz - 1);
}
// ------------------------------------------------------------
// 1. Separate Chaining
// ------------------------------------------------------------
template <typename Key, typename Value>
class ChainingHashTable
{
private:
    vector<list<pair<Key, Value>>> tb;
    ll sz = ::size, elmnt = 0, cols = 0, ins_exp = 0, del_com = 0;
    int hash_num;
    ll getIndex(const Key &key) const
    {
        return pri_hash(key, hash_num, sz);
    }
    void rehash(ll news)
    {
        vector<pair<Key, Value>> items;
        for (auto &b : tb)
        {
            for (auto &i : b)
            {
                items.pb(i);
            }
        }
        sz = news;
        tb.clear();
        tb.resize(sz);
        for (auto &i : items)
        {
            tb[getIndex(i.first)].push_back(i);
        }
    }
    void Exp_chk()
    {
        ll need = (elmnt + 1) / 2;
        if ((double)elmnt / sz > MAX_LOAD && ins_exp >= need)
        {
            rehash(porer_prime(2 * sz));
            ins_exp = 0;
        }
    }
    void com_chk()
    {
        ll need = (elmnt + 1) / 2;
        if (sz != ::size && (double)elmnt / sz < MIN_LOAD && del_com >= need)
        {
            ll newSize = max(::size, ager_prime(sz / 2));
            rehash(newSize);
            del_com = 0;
        }
    }

public:
    ChainingHashTable(int selectedHash)
    {
        hash_num = selectedHash;
        tb.resize(sz);
    }
    bool insert(const Key &key, const Value &value)
    {
        ll index = getIndex(key);
        for (auto &item : tb[index])
        {
            if (item.first == key)
            {
                item.second = value;
                return false;
            }
        }
        cols += tb[index].size();
        tb[index].push_back({key, value});
        elmnt++;
        ins_exp++;
        Exp_chk();
        return true;
    }
    bool search(const Key &key, Value &x, ll &hits) const
    {
        hits = 0;
        for (auto &item : tb[getIndex(key)])
        {
            hits++;
            if (item.first == key)
            {
                x = item.second;
                return true;
            }
        }
        return false;
    }
    bool erase(const Key &key)
    {
        ll index = getIndex(key);
        for (auto it = tb[index].begin(); it != tb[index].end(); it++)
        {
            if (it->first == key)
            {
                tb[index].erase(it);
                elmnt--;
                del_com++;
                com_chk();
                return true;
            }
        }
        return false;
    }
    ll cols_count() const
    {
        return cols;
    }
};
// ------------------------------------------------------------
// 2. Double Hashing
// ------------------------------------------------------------
template <typename Key, typename Value>
class DoubleHashTable
{
private:
    vector<pair<Key, Value>> tb;
    vector<int> state; // 0 = empty, 1 = occupied, 2 = deleted
    ll sz = ::size, elmnt = 0, cols = 0, ins_exp = 0, del_com = 0;
    int hash_num;
    ll probe(const Key &key, ll i) const
    {
        ull h = pri_hash(key, hash_num, sz);
        ull step = aux_Hash(key_theke_string(key), sz);
        return (h + i * step) % sz;
    }
    void table_banao()
    {
        tb.clear();
        tb.resize(sz);
        state.assign(sz, 0);
    }
    void place(const Key &key, const Value &value)
    {
        loop(i, 0, sz)
        {
            ll index = probe(key, i);
            if (state[index] != 1)
            {
                tb[index] = {key, value};
                state[index] = 1;
                return;
            }
        }
    }
    void rehash(ll newSize)
    {
        vector<pair<Key, Value>> items;
        loop(i, 0, sz)
        {
            if (state[i] == 1)
            {
                items.pb(tb[i]);
            }
        }
        sz = newSize;
        table_banao();
        for (auto &item : items)
        {
            place(item.first, item.second);
        }
    }
    void Exp_chk()
    {
        ll need = (elmnt + 1) / 2;
        if ((double)elmnt / sz > MAX_LOAD &&
            ins_exp >= need)
        {
            rehash(porer_prime(2 * sz));
            ins_exp = 0;
        }
    }
    void com_chk()
    {
        ll need = (elmnt + 1) / 2;
        if (sz != ::size &&
            (double)elmnt / sz < MIN_LOAD &&
            del_com >= need)
        {
            ll newSize = max(::size, ager_prime(sz / 2));
            rehash(newSize);
            del_com = 0;
        }
    }

public:
    DoubleHashTable(int selectedHash)
    {
        hash_num = selectedHash;
        table_banao();
    }
    bool insert(const Key &key, const Value &value)
    {
        ll del_idx = -1;
        loop(i, 0, sz)
        {
            ll index = probe(key, i);
            if (state[index] == 1)
            {
                if (tb[index].first == key)
                {
                    tb[index].second = value;
                    return false;
                }
                cols++;
            }
            else if (state[index] == 2)
            {
                if (del_idx == -1)
                {
                    del_idx = index;
                }
            }
            else
            {
                if (del_idx != -1)
                {
                    index = del_idx;
                }
                tb[index] = {key, value};
                state[index] = 1;
                elmnt++;
                ins_exp++;
                Exp_chk();
                return true;
            }
        }
        if (del_idx != -1)
        {
            tb[del_idx] = {key, value};
            state[del_idx] = 1;
            elmnt++;
            ins_exp++;
            Exp_chk();
            return true;
        }
        return false;
    }
    bool search(const Key &key, Value &value, ll &hits) const
    {
        hits = 0;
        loop(i, 0, sz)
        {
            ll index = probe(key, i);
            hits++;
            if (state[index] == 0)
            {
                return false;
            }
            if (state[index] == 1 && tb[index].first == key)
            {
                value = tb[index].second;
                return true;
            }
        }
        return false;
    }
    bool erase(const Key &key)
    {
        loop(i, 0, sz)
        {
            ll index = probe(key, i);
            if (state[index] == 0)
            {
                return false;
            }
            if (state[index] == 1 && tb[index].first == key)
            {
                state[index] = 2;
                elmnt--;
                del_com++;
                com_chk();
                return true;
            }
        }
        return false;
    }
    ll cols_count() const
    {
        return cols;
    }
};
// ------------------------------------------------------------
// 3. Custom Probing
// ------------------------------------------------------------
template <typename Key, typename Value>
class CustomHashTable
{
private:
    vector<pair<Key, Value>> tb;
    vector<int> state; // 0 = empty, 1 = occupied, 2 = deleted
    ll sz = ::size;
    ll elmnt = 0;
    ll cols = 0;
    ll ins_exp = 0;
    ll del_com = 0;
    int hash_num;
    ll probe(const Key &key, ll i) const
    {
        ull h = pri_hash(key, hash_num, sz);
        ull step = aux_Hash(key_theke_string(key), sz);
        return (h + C1 * i * step + C2 * i * i) % sz;
    }
    void table_banao()
    {
        tb.clear();
        tb.resize(sz);
        state.assign(sz, 0);
    }
    void place(const Key &key, const Value &value)
    {
        loop(i, 0, sz)
        {
            ll index = probe(key, i);
            if (state[index] != 1)
            {
                tb[index] = {key, value};
                state[index] = 1;
                return;
            }
        }
    }
    void rehash(ll newSize)
    {
        vector<pair<Key, Value>> items;
        loop(i, 0, sz)
        {
            if (state[i] == 1)
            {
                items.pb(tb[i]);
            }
        }
        sz = newSize;
        table_banao();
        for (auto &item : items)
        {
            place(item.first, item.second);
        }
    }
    void Exp_chk()
    {
        ll need = (elmnt + 1) / 2;
        if ((double)elmnt / sz > MAX_LOAD &&
            ins_exp >= need)
        {
            rehash(porer_prime(2 * sz));
            ins_exp = 0;
        }
    }
    void com_chk()
    {
        ll need = (elmnt + 1) / 2;
        if (sz != ::size &&
            (double)elmnt / sz < MIN_LOAD &&
            del_com >= need)
        {
            ll newSize = max(::size, ager_prime(sz / 2));
            rehash(newSize);
            del_com = 0;
        }
    }

public:
    CustomHashTable(int selectedHash)
    {
        hash_num = selectedHash;
        table_banao();
    }
    bool insert(const Key &key, const Value &value)
    {
        ll del_idx = -1;
        loop(i, 0, sz)
        {
            ll index = probe(key, i);
            if (state[index] == 1)
            {
                if (tb[index].first == key)
                {
                    tb[index].second = value;
                    return false;
                }
                cols++;
            }
            else if (state[index] == 2)
            {
                if (del_idx == -1)
                {
                    del_idx = index;
                }
            }
            else
            {
                if (del_idx != -1)
                {
                    index = del_idx;
                }
                tb[index] = {key, value};
                state[index] = 1;
                elmnt++;
                ins_exp++;
                Exp_chk();
                return true;
            }
        }
        if (del_idx != -1)
        {
            tb[del_idx] = {key, value};
            state[del_idx] = 1;
            elmnt++;
            ins_exp++;
            Exp_chk();
            return true;
        }
        return false;
    }
    bool search(const Key &key, Value &value, ll &hits) const
    {
        hits = 0;
        loop(i, 0, sz)
        {
            ll index = probe(key, i);
            hits++;
            if (state[index] == 0)
            {
                return false;
            }
            if (state[index] == 1 && tb[index].first == key)
            {
                value = tb[index].second;
                return true;
            }
        }
        return false;
    }
    bool erase(const Key &key)
    {
        loop(i, 0, sz)
        {
            ll index = probe(key, i);
            if (state[index] == 0)
            {
                return false;
            }
            if (state[index] == 1 && tb[index].first == key)
            {
                state[index] = 2;
                elmnt--;
                del_com++;
                com_chk();
                return true;
            }
        }
        return false;
    }
    ll cols_count() const
    {
        return cols;
    }
};
vector<string> Word_banao(ll total, ll l)
{
    vector<string> words;
    while ((ll)words.size() < total)
    {
        string word = "";
        loop(i, 0, l)
        {
            word += char('a' + rand() % 26);
        }

        bool duplicate = false;
        for (auto &x : words)
        {
            if (x == word)
            {
                duplicate = true;
                break;
            }
        }

        if (!duplicate)
        {
            words.pb(word);
        }
    }
    return words;
}
using Result = pair<ll, double>; // {collisions, average hits}
template <typename Table>
Result Exp_chalao(int hash_num, const vector<string> &words, const vector<ll> &sample)
{
    Table hashTable(hash_num);
    loop(i, 0, (ll)words.size())
    {
        hashTable.insert(words[i], i + 1);
    }
    ll totalHits = 0, value;
    for (ll index : sample)
    {
        ll hits;
        hashTable.search(words[index], value, hits);
        totalHits += hits;
    }
    return {hashTable.cols_count(), (double)totalHits / sample.size()};
}
void dekhao(Result ans[3][2])
{
    vector<string> names = {
        "Chaining Method", "Double Hashing", "Custom Probing"};
    cout << left << setw(20) << "Method"
         << setw(18) << "Hash1 Collision"
         << setw(15) << "Hash1 Hits"
         << setw(18) << "Hash2 Collision"
         << "Hash2 Hits" << tata;
    cout << fixed << setprecision(3);
    loop(i, 0, 3)
    {
        cout << setw(20) << names[i]
             << setw(18) << ans[i][0].first
             << setw(15) << ans[i][0].second
             << setw(18) << ans[i][1].first
             << ans[i][1].second << tata;
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    ll w = 10000, search = 1000, l;
    cin >> l;
    if (l < 3)
    {
        cout << "Length must be at least 3 for 10000 unique words." << tata;
        return 0;
    }
    vector<string> words = Word_banao(w, l);
    vector<ll> id(w);
    iota(id.begin(), id.end(), 0);
    for (ll i = w - 1; i > 0; i--)
    {
        swap(id[i], id[rand() % (i + 1)]);
    }
    vector<ll> sample(id.begin(), id.begin() + search);
    Result ans[3][2];
    loop(hash_num, 1, 3)
    {
        ans[0][hash_num - 1] = Exp_chalao<ChainingHashTable<string, ll>>(hash_num, words, sample);
        ans[1][hash_num - 1] = Exp_chalao<DoubleHashTable<string, ll>>(hash_num, words, sample);
        ans[2][hash_num - 1] = Exp_chalao<CustomHashTable<string, ll>>(hash_num, words, sample);
    }
    dekhao(ans);
    return 0;
}
