#include <bits/stdc++.h>
using namespace std;

const int INIT_SIZE = 13;
const double MAX_LOAD = 0.50;
const double MIN_LOAD = 0.25;
const int TOTAL_KEYS = 10000;
const int TO_SEARCHES = 1000;
const int C1 = 1, C2 = 3;

string keyString(char key)
{
    return string(1, key);
}

string keyString(const string &key)
{
    return key;
}

template <typename K>
string keyString(const K &key)
{
    return to_string(key);
}

template <typename K>
unsigned long long makeHash(const K &key, int base)
{
    unsigned long long hashVal = 0;
    string text = keyString(key);
    
    for (char ch : text)
    {
        hashVal = hashVal * base + ch;
    }
    return hashVal;
}

template <typename K>
int primaryHash(const K &key, int tableSize, int hashNo)
{
    int base = (hashNo == 1 ? 31 : 37);
    return makeHash(key, base) % tableSize;
}

template <typename K>int auxiliaryHash(const K &key, int tableSize)
{
    return 1 + makeHash(key, 41) % (tableSize - 1);
}

bool isPrime(int n)
{
    if (n < 2)
    {
        return false;
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

int nextPrime(int n)
{
    n++;
    while (!isPrime(n))
    {
        n++;
    }
    return n;
}

int previousPrime(int n)
{
    n--;
    while (n > INIT_SIZE && !isPrime(n))
    {
        n--;
    }
    return max(n, INIT_SIZE);
}

template <typename K, typename V>
class ChainHash
{
    vector<list<pair<K, V>>> table;
    int tableSize, elementCount, hashChoice;
    long long collisions;
    int insertedAfterGrow, deletedAfterShrink;
    int lastGrowCount, lastShrinkCount;

    double loadFactor()
    {
        return (double)elementCount / tableSize;
    }

    int indexOf(const K &key)
    {
        return primaryHash(key, tableSize, hashChoice);
    }

    void resizeTable(int newSize)
    {
        vector<list<pair<K, V>>> oldTable = table;
        tableSize = newSize;
        table.assign(tableSize, {});

        for (auto &chain : oldTable)
        {
            for (auto &item : chain)
            {
                table[indexOf(item.first)].push_back(item);
            }
        }
    }

    void checkGrow()
    {
        if (loadFactor() > MAX_LOAD && insertedAfterGrow >= lastGrowCount / 2)
        {
            resizeTable(nextPrime(2 * tableSize));
            lastGrowCount = elementCount;
            insertedAfterGrow = 0;

            if (lastShrinkCount == 0)
            {
                lastShrinkCount = elementCount;
                deletedAfterShrink = 0;
            }
        }
    }

    void checkShrink()
    {
        if (tableSize > INIT_SIZE && loadFactor() < MIN_LOAD && deletedAfterShrink >= lastShrinkCount / 2)
        {
            resizeTable(previousPrime(tableSize / 2));
            lastShrinkCount = elementCount;
            deletedAfterShrink = 0;
        }
    }

public:
    ChainHash(int choice = 1)
    {
        tableSize = INIT_SIZE;
        elementCount = 0;
        hashChoice = choice;
        collisions = 0;
        insertedAfterGrow = 0;
        deletedAfterShrink = 0;
        lastGrowCount = 0;
        lastShrinkCount = 0;
        table.resize(tableSize);
    }

    void insert(const K &key, const V &value)
    {
        int index = indexOf(key);

        for (auto &item : table[index])
        {
            if (item.first == key)
            {
                item.second = value;
                return;
            }
        }

        if (!table[index].empty())
        {
            collisions++;
        }
        
        table[index].push_back({key, value});
        elementCount++;
        insertedAfterGrow++;
        
        checkGrow();
    }

    bool search(const K &key, V &value, int &hits)
    {
        hits = 0;

        for (auto &item : table[indexOf(key)])
        {
            hits++;

            if (item.first == key)
            {
                value = item.second;
                return true;
            }
        }

        return false;
    }

    bool deleteKey(const K &key)
    {
        int index = indexOf(key);

        for (auto it = table[index].begin(); it != table[index].end(); it++)
        {
            if (it->first == key)
            {
                table[index].erase(it);
                elementCount--;
                deletedAfterShrink++;
                
                checkShrink();
                return true;
            }
        }

        return false;
    }

    long long getCollisions()
    {
        return collisions;
    }
};

template <typename K, typename V>
struct Slot
{
    K key;
    V value;
    int state = 0; 
};

template <typename K, typename V>
class OpenAddressHashTable
{
    vector<Slot<K, V>> table;
    vector<int> primaryCount;
    int tableSize, elementCount, hashChoice;
    long long collisions;
    bool customProbing;
    int insertedAfterGrow, deletedAfterShrink;
    int lastGrowCount, lastShrinkCount;

    double loadFactor()
    {
        return (double)elementCount / tableSize;
    }

    int probeIndex(const K &key, int i)
    {
        long long h1 = primaryHash(key, tableSize, hashChoice);
        long long h2 = auxiliaryHash(key, tableSize);

        if (!customProbing)
        {
            return (h1 + i * h2) % tableSize;
        }
        
        return (h1 + C1 * i * h2 + C2 * 1LL * i * i) % tableSize;
    }

    bool place(const K &key, const V &value)
    {
        for (int i = 0; i < tableSize; i++)
        {
            int index = probeIndex(key, i);
            
            if (table[index].state != 1)
            {
                table[index].key = key;
                table[index].value = value;
                table[index].state = 1;
                return true;
            }
        }
        return false;
    }

    void resizeTable(int newSize)
    {
        vector<Slot<K, V>> oldTable = table;

        while (true)
        {
            tableSize = newSize;
            table.assign(tableSize, {});
            primaryCount.assign(tableSize, 0);
            bool success = true;

            for (auto &slot : oldTable)
            {
                if (slot.state == 1 && !place(slot.key, slot.value))
                {
                    success = false;
                    break;
                }
            }

            if (success)
            {
                for (auto &slot : oldTable)
                {
                    if (slot.state == 1)
                    {
                        primaryCount[primaryHash(slot.key, tableSize, hashChoice)]++;
                    }
                }
                return;
            }
            
            newSize = nextPrime(2 * newSize);
        }
    }

    void growNow()
    {
        resizeTable(nextPrime(2 * tableSize));
        lastGrowCount = elementCount;
        insertedAfterGrow = 0;

        if (lastShrinkCount == 0)
        {
            lastShrinkCount = elementCount;
            deletedAfterShrink = 0;
        }
    }

    void checkGrow()
    {
        if (loadFactor() > MAX_LOAD && insertedAfterGrow >= lastGrowCount / 2)
        {
            growNow();
        }
    }

    void checkShrink()
    {
        if (tableSize > INIT_SIZE && loadFactor() < MIN_LOAD && deletedAfterShrink >= lastShrinkCount / 2)
        {
            resizeTable(previousPrime(tableSize / 2));
            lastShrinkCount = elementCount;
            deletedAfterShrink = 0;
        }
    }

public:
    OpenAddressHashTable(int choice, bool custom)
    {
        tableSize = INIT_SIZE;
        elementCount = 0;
        hashChoice = choice;
        collisions = 0;
        customProbing = custom;
        insertedAfterGrow = 0;
        deletedAfterShrink = 0;
        lastGrowCount = 0;
        lastShrinkCount = 0;
        table.resize(tableSize);
        primaryCount.assign(tableSize, 0);
    }

    void insert(const K &key, const V &value)
    {
        int firstDeleted = -1;

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
            }
            else if (table[index].state == 2)
            {
                if (firstDeleted == -1)
                {
                    firstDeleted = index;
                }
            }
            else
            {
                if (firstDeleted != -1)
                {
                    index = firstDeleted;
                }

                int home = primaryHash(key, tableSize, hashChoice);
                
                if (primaryCount[home] > 0)
                {
                    collisions++;
                }
                primaryCount[home]++;

                table[index] = {key, value, 1};
                elementCount++;
                insertedAfterGrow++;
                
                checkGrow();
                return;
            }
        }

        if (firstDeleted != -1)
        {
            int home = primaryHash(key, tableSize, hashChoice);
            
            if (primaryCount[home] > 0)
            {
                collisions++;
            }
            primaryCount[home]++;

            table[firstDeleted] = {key, value, 1};
            elementCount++;
            insertedAfterGrow++;
            
            checkGrow();
            return;
        }

        growNow();
        insert(key, value);
    }

    bool search(const K &key, V &value, int &hits)
    {
        hits = 0;

        for (int i = 0; i < tableSize; i++)
        {
            int index = probeIndex(key, i);
            
            if (table[index].state == 0)
            {
                return false;
            }

            if (table[index].state == 1)
            {
                hits++;
                if (table[index].key == key)
                {
                    value = table[index].value;
                    return true;
                }
            }
        }

        return false;
    }

    bool deleteKey(const K &key)
    {
        for (int i = 0; i < tableSize; i++)
        {
            int index = probeIndex(key, i);
            
            if (table[index].state == 0)
            {
                return false;
            }

            if (table[index].state == 1 && table[index].key == key)
            {
                int home = primaryHash(key, tableSize, hashChoice);
                primaryCount[home]--;
                
                table[index].state = 2;
                elementCount--;
                deletedAfterShrink++;
                
                checkShrink();
                return true;
            }
        }

        return false;
    }

    long long getCollisions()
    {
        return collisions;
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

vector<string> generateWords(int length)
{
    set<string> used;
    vector<string> words;

    while ((int)words.size() < TOTAL_KEYS)
    {
        string word = randomWord(length);
        if (used.insert(word).second)
        {
            words.push_back(word);
        }
    }
    return words;
}

template <typename Table>
pair<long long, double> testTable(Table &table, const vector<string> &words, const vector<int> &searchIndex)
{
    for (int i = 0; i < TOTAL_KEYS; i++)
    {
        table.insert(words[i], i + 1);
    }

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

    const int wordLength = 10;

    vector<string> words = generateWords(wordLength);
    vector<int> searchIndex(TO_SEARCHES);
    
    for (int i = 0; i < TO_SEARCHES; i++)
    {
        searchIndex[i] = rand() % TOTAL_KEYS;
    }

    long long collision[3][2];
    double hits[3][2];

    for (int hashChoice = 1; hashChoice <= 2; hashChoice++)
    {
        ChainHash<string, int> chaining(hashChoice);
        OpenAddressHashTable<string, int> doubleHashing(hashChoice, false);
        OpenAddressHashTable<string, int> customProbing(hashChoice, true);

        pair<long long, double> a = testTable(chaining, words, searchIndex);
        pair<long long, double> b = testTable(doubleHashing, words, searchIndex);
        pair<long long, double> c = testTable(customProbing, words, searchIndex);

        collision[0][hashChoice - 1] = a.first;
        hits[0][hashChoice - 1] = a.second;
        
        collision[1][hashChoice - 1] = b.first;
        hits[1][hashChoice - 1] = b.second;
        
        collision[2][hashChoice - 1] = c.first;
        hits[2][hashChoice - 1] = c.second;
    }

    string method[3] = {"Chaining Method", "Double Hashing", "Custom Probing"};
    
    cout << left << setw(20) << "Method" << setw(20) << "Hash1 Collision" << setw(15) << "Hash1 Hits" << setw(20) << "Hash2 Collision" << setw(15) << "Hash2 Hits" << '\n';
         
    for (int i = 0; i < 3; i++)
    {
        cout << left << setw(20) << method[i] << setw(20) << collision[i][0] << setw(15) << hits[i][0] << setw(20) << collision[i][1] << setw(15) << hits[i][1] << '\n';
    }

    return 0;
}