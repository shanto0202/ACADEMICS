#include <bits/stdc++.h>
using namespace std;

const int INIT_SIZE = 13;
const double MAX_LOAD = 0.50;
const double MIN_LOAD = 0.25;
const int TOTAL_KEYS = 10000;
const int TO_SEARCHES = 1000;

// ======================== HASH CHANGE AREA ========================
int primaryHash(const string &key, int Size, int hashNo)
{
    // General polynomial hash. Replace only this body when a new hash is given.
    unsigned long long value = 0;
    int base = (hashNo == 1 ? 31 : 37);
    for (unsigned char ch : key) value = value * base + ch;
    return value % Size;
}

// ====================== STRUCTURE CHANGE AREA =====================
template <typename K, typename V>
struct blk
{
    K key;
    V value;

    // Future modification examples:
    // double weight;
    // int frequency;
    // long long insertionTime;

    blk(const K &k, const V &v) : key(k), value(v)
    {
        // If a field is added, calculate/initialize it here.
        // weight = weightFunction(k);
        // frequency = 1;
    }
};

bool isPrime(int n)
{
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int nextPrime(int n)
{
    do n++; while (!isPrime(n));
    return n;
}

int previousPrime(int n)
{
    n--;
    while (n > INIT_SIZE && !isPrime(n)) n--;
    return max(n, INIT_SIZE);
}

template <typename K, typename V>
class ChainHash
{
    vector<list<blk<K, V>>> table;
    int Size, elements, hashNo;
    long long collisions;

    double loadFactor() const { return (double)elements / Size; }
    int indexOf(const K &key) const { return primaryHash(key, Size, hashNo); }

    void resizeTable(int newSize)
    {
        auto oldTable = table;
        Size = newSize;
        table.assign(Size, {});

        for (auto &chain : oldTable)
            for (auto &node : chain)
                table[indexOf(node.key)].push_back(node);
    }

    void checkGrow()
    {
        if (loadFactor() > MAX_LOAD)
            resizeTable(nextPrime(2 * Size));
    }

    void checkShrink()
    {
        if (Size > INIT_SIZE && loadFactor() < MIN_LOAD)
            resizeTable(previousPrime(Size / 2));
    }

public:
    void insert(const K &key, const V &value)
    {
        int index = indexOf(key);
        auto &chain = table[index];

        // Duplicate check must happen before collision counting.
        for (auto &node : chain)
        {
            if (node.key == key)
            {
                node.value = value;
                return;
            }
        }

        if (!chain.empty()) collisions++;
        // ===================== INSERT CHANGE AREA =====================
        // Default rule: append at the end of the chain.
        chain.push_back(blk<K, V>(key, value));

        // If sorted insertion is asked, replace push_back with:
        // blk<K,V> newBlock(key, value);
        // auto it = chain.begin();
        // while (it != chain.end() && it->weight >= newBlock.weight) it++;
        // chain.insert(it, newBlock);

        elements++;
        checkGrow();
    }

    bool search(const K &key, V &value, int &hits) const
    {
        hits = 0;
        for (const auto &node : table[indexOf(key)])
        {
            hits++;
            if (node.key == key)
            {
                value = node.value;
                return true;
            }
        }
        return false;
    }

    bool deleteKey(const K &key)
    {
        auto &chain = table[indexOf(key)];
        for (auto it = chain.begin(); it != chain.end(); it++)
        {
            if (it->key == key)
            {
                chain.erase(it);
                elements--;
                checkShrink();
                return true;
            }
        }
        return false;
    }

    void display() const
    {
        for (int i = 0; i < Size; i++)
        {
            if (table[i].empty()) continue;
            cout << "Bucket " << i << ": ";
            for (const auto &node : table[i])
                cout << "[" << node.key << ", " << node.value << "] -> ";
            cout << "NULL\n";
        }
    }

    long long getCollisions() const { return collisions; }

    ChainHash(int choice = 1)
    {
        Size = INIT_SIZE;
        elements = 0;
        hashNo = choice;
        collisions = 0;
        table.resize(Size);
    }
};

string randomWord(int length)
{
    string word;
    for (int i = 0; i < length; i++) word += char('a' + rand() % 26);
    return word;
}

vector<string> genWords(int length)
{
    set<string> used;
    vector<string> words;
    while ((int)words.size() < TOTAL_KEYS)
    {
        string word = randomWord(length);
        if (used.insert(word).second) words.push_back(word);
    }
    return words;
}

template <typename Table>
pair<long long, double> testTable(Table &table, const vector<string> &words,
                                  const vector<int> &searchIndex)
{
    for (int i = 0; i < TOTAL_KEYS; i++) table.insert(words[i], i + 1);
    long long totalHits = 0;
    for (int index : searchIndex)
    {
        int value, hits;
        table.search(words[index], value, hits);
        totalHits += hits;
    }
    return {table.getCollisions(), (double)totalHits / TO_SEARCHES};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));

    vector<string> words = genWords(10);
    vector<int> searchIndex(TO_SEARCHES);
    for (int i = 0; i < TO_SEARCHES; i++) searchIndex[i] = rand() % TOTAL_KEYS;

    long long collision[2];
    double hits[2];
    for (int hashNo = 1; hashNo <= 2; hashNo++)
    {
        ChainHash<string, int> chaining(hashNo);
        auto result = testTable(chaining, words, searchIndex);
        collision[hashNo - 1] = result.first;
        hits[hashNo - 1] = result.second;
    }
    cout << left << setw(20) << "Method" << setw(20) << "Hash1 Collision"
         << setw(15) << "Hash1 Hits" << setw(20) << "Hash2 Collision"
         << setw(15) << "Hash2 Hits" << '\n';
    cout << left << setw(20) << "Chaining Method" << setw(20) << collision[0]
         << setw(15) << hits[0] << setw(20) << collision[1] << setw(15) << hits[1] << '\n';
    return 0;
}
