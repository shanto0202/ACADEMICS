#include <bits/stdc++.h>
using namespace std;

const int INITIAL_SIZE = 13;
const double UPPER_LOAD = 0.50;
const double LOWER_LOAD = 0.25;
const bool ENABLE_RESIZE = false; // Question says fixed table size N = 13.

// ======================== HASH CHANGE AREA ========================
int hash1(const string &key, int tableSize)
{
    // General polynomial hash. Replace only this body when a new hash is given.
    unsigned long long value = 0;
    // for (unsigned char ch : key)
    //     value = value * 31 + ch;
    // return value % tableSize;
    for(int i=1;i<=(int)key.size();i++){
        value+=i*key[i-1];
    }
    return value%tableSize;
}

double wFunc(const string &key){
    double weight=(key[0]+key[(int)key.size()-1])%100;
    return weight/100;
}

// ====================== STRUCTURE CHANGE AREA =====================
template <typename K, typename V>
struct Block
{
    K key;
    V value;
    double weight;

    // Future modification examples:
    // double weight;
    // int frequency;
    // long long insertionTime;

    Block(const K &k, const V &v) 
    {
        key = k;
        value = v;
        weight=wFunc(k);
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
    while (n > INITIAL_SIZE && !isPrime(n)) n--;
    return max(n, INITIAL_SIZE);
}

template <typename K, typename V>
class ChainingHashTable
{
    vector<list<Block<K, V>>> table;
    int tableSize = INITIAL_SIZE;
    int elements = 0;
    long long collisions = 0;

    double loadFactor() const { return (double)elements / tableSize; }
    
    int indexOf(const K &key) const { return hash1(key, tableSize); }

    void resizeTable(int newSize)
    {
        auto oldTable = table;
        tableSize = newSize;
        table.assign(tableSize, {});

        for (auto &chain : oldTable)
            for (auto &node : chain)
                table[indexOf(node.key)].push_back(node);
    }

    void checkGrow()
    {
        if (ENABLE_RESIZE && loadFactor() > UPPER_LOAD)
            resizeTable(nextPrime(2 * tableSize));
    }

    void checkShrink()
    {
        if (ENABLE_RESIZE && tableSize > INITIAL_SIZE && loadFactor() < LOWER_LOAD)
            resizeTable(previousPrime(tableSize / 2));
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
        chain.push_back(Block<K, V>(key, value));

        // If sorted insertion is asked, replace push_back with:
        // Block<K,V> newBlock(key, value);
        // auto it = chain.begin();
        // while (it != chain.end() && it->weight >= newBlock.weight) it++;
        // chain.insert(it, newBlock);

        elements++;
        checkGrow();
    }

    void sortAllChains()
    {
        for (auto &chain : table)
        {
            chain.sort([](const Block<K, V> &a, const Block<K, V> &b)
            {
                return a.weight > b.weight;
            });
        }
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

    bool erase(const K &key)
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
        cout << fixed << setprecision(2);

        for (int i = 0; i < tableSize; i++)
        {
            if (table[i].empty()) continue;
            cout << "Bucket " << i << ": ";
            for (const auto &node : table[i])
                cout << node.key << " (" << node.weight << ") -> ";
            cout << "NULL\n";
        }
    }

    long long getCollisions() const { return collisions; }

    ChainingHashTable() { table.resize(tableSize); }
};

int main()
{
    ChainingHashTable<string, int> ht;

    vector<string> words =
    {
        "cat", "dog", "bat", "rat", "sun", "fun",
        "run", "top", "pot", "opt", "art", "tar"
    };

    for (int i = 0; i < (int)words.size(); i++)
        ht.insert(words[i], i + 1);

    ht.sortAllChains();

    ht.display();
    return 0;
}
