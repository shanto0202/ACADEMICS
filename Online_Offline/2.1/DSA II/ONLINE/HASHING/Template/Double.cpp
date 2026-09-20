#include <bits/stdc++.h>
using namespace std;

const int INITIAL_SIZE = 13;
const double UPPER_LOAD = 0.50;
const double LOWER_LOAD = 0.25;
const bool ENABLE_RESIZE = true;

// ======================== HASH CHANGE AREA ========================
int hash1(const string &key, int tableSize)
{
    unsigned long long value = 0;
    for (unsigned char ch : key) value = value * 31 + ch;
    return value % tableSize;
}

int auxiliaryHash(const string &key, int tableSize)
{
    unsigned long long value = 0;
    for (unsigned char ch : key) value = value * 41 + ch;
    return 1 + value % (tableSize - 1);
}

// state: 0 = never used, 1 = occupied, 2 = deleted
// ====================== STRUCTURE CHANGE AREA =====================
template <typename K, typename V>
struct Block
{
    K key{};
    V value{};
    int state = 0;

    // Future modification examples:
    // double weight = 0;
    // int frequency = 0;
    // long long insertionTime = 0;
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
class DoubleHashTable
{
    vector<Block<K, V>> table;
    int tableSize = INITIAL_SIZE;
    int elements = 0;
    long long collisions = 0;

    double loadFactor() const { return (double)elements / tableSize; }

    // ====================== PROBE CHANGE AREA ======================
    int probeIndex(const K &key, int i) const
    {
        int h1 = hash1(key, tableSize);
        int h2 = auxiliaryHash(key, tableSize);
        return (h1 + 1LL * i * h2) % tableSize;
    }

    bool placeWithoutCounting(const K &key, const V &value)
    {
        for (int i = 0; i < tableSize; i++)
        {
            int index = probeIndex(key, i);
            if (table[index].state != 1)
            {
                table[index] = {key, value, 1};
                return true;
            }
        }
        return false;
    }

    void resizeTable(int newSize)
    {
        auto oldTable = table;
        while (true)
        {
            tableSize = newSize;
            table.assign(tableSize, {});
            bool ok = true;

            for (auto &slot : oldTable)
                if (slot.state == 1 &&
                    !placeWithoutCounting(slot.key, slot.value))
                {
                    ok = false;
                    break;
                }

            if (ok) return;
            newSize = nextPrime(2 * newSize);
        }
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
    DoubleHashTable() { table.resize(tableSize); }

    void insert(const K &key, const V &value)
    {
        int firstDeleted = -1;

        // ===================== INSERT CHANGE AREA =====================
        for (int i = 0; i < tableSize; i++)
        {
            int index = probeIndex(key, i);

            if (table[index].state == 1)
            {
                if (table[index].key == key)
                {
                    table[index].value = value;
                    return;
                }
                collisions++; // Every occupied unequal slot is one probe collision.
            }
            else if (table[index].state == 2)
            {
                if (firstDeleted == -1) firstDeleted = index;
            }
            else
            {
                if (firstDeleted != -1) index = firstDeleted;
                table[index] = {key, value, 1};
                // If weight is added: table[index].weight = weightFunction(key);
                elements++;
                checkGrow();
                return;
            }
        }

        if (firstDeleted != -1)
        {
            table[firstDeleted] = {key, value, 1};
            // If weight is added: table[firstDeleted].weight = weightFunction(key);
            elements++;
            checkGrow();
            return;
        }

        resizeTable(nextPrime(2 * tableSize));
        insert(key, value);
    }

    bool search(const K &key, V &value, int &hits) const
    {
        hits = 0;
        for (int i = 0; i < tableSize; i++)
        {
            int index = probeIndex(key, i);
            hits++;
            if (table[index].state == 0) return false;
            if (table[index].state == 1 && table[index].key == key)
            {
                value = table[index].value;
                return true;
            }
        }
        return false;
    }

    bool erase(const K &key)
    {
        for (int i = 0; i < tableSize; i++)
        {
            int index = probeIndex(key, i);
            if (table[index].state == 0) return false;
            if (table[index].state == 1 && table[index].key == key)
            {
                table[index].state = 2;
                elements--;
                checkShrink();
                return true;
            }
        }
        return false;
    }

    void display() const
    {
        for (int i = 0; i < tableSize; i++)
        {
            cout << i << ": ";
            if (table[i].state == 1)
                cout << "[" << table[i].key << ", " << table[i].value << "]";
            else if (table[i].state == 2) cout << "DELETED";
            else cout << "EMPTY";
            cout << '\n';
        }
    }

    long long getCollisions() const { return collisions; }
};

int main()
{
    DoubleHashTable<string, int> ht;
    int n;
    cin >> n;

    while (n--)
    {
        string key;
        int value;
        cin >> key >> value;
        ht.insert(key, value);
    }

    ht.display();
    return 0;
}
