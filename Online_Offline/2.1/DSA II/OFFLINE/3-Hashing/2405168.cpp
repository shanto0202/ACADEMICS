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
        hashVal = hashVal * base + ch;

    return hashVal;
}

template <typename K>
int primaryHash(const K &key, int Size, int hashNo)
{
    int base = (hashNo == 1 ? 31 : 37);
    return makeHash(key, base) % Size;
}

template <typename K>
int auxiliaryHash(const K &key, int Size)
{
    return 1 + makeHash(key, 41) % (Size - 1);
}

bool isPrime(int n)
{
    if (n < 2)
        return false;

    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;

    return true;
}

int nextPrime(int n)
{
    n++;

    while (!isPrime(n))
        n++;

    return n;
}

int previousPrime(int n)
{
    n--;

    while (n > INIT_SIZE && !isPrime(n))
        n--;

    return max(n, INIT_SIZE);
}

template <typename K, typename V>
class ChainHash
{
    vector<list<pair<K, V>>> table;
    int Size, elements, hashNo;
    long long collisions;
    int inAftExp, delAftShrink;
    int elmOflastExp, elmOflastShrink;

    double loadFactor()
    {
        return (double)elements / Size;
    }

    int indexOf(const K &key)
    {
        return primaryHash(key, Size, hashNo);
    }

    void resizeTable(int newSize)
    {
        vector<list<pair<K, V>>> oldTable = table;

        Size = newSize;
        table.assign(Size, {});

        for (auto &chain : oldTable)
            for (auto &item : chain)
                table[indexOf(item.first)].push_back(item);
    }

    void checkGrow()
    {
        if (loadFactor() > MAX_LOAD && inAftExp >= elmOflastExp / 2)
        {
            resizeTable(nextPrime(2 * Size));
            elmOflastExp = elements;
            inAftExp = 0;

            if (elmOflastShrink == 0)
            {
                elmOflastShrink = elements;
                delAftShrink = 0;
            }
        }
    }

    void checkShrink()
    {
        if (Size > INIT_SIZE && loadFactor() < MIN_LOAD &&
            delAftShrink >= elmOflastShrink / 2)
        {
            resizeTable(previousPrime(Size / 2));
            elmOflastShrink = elements;
            delAftShrink = 0;
        }
    }

public:
    ChainHash(int choice = 1)
    {
        Size = INIT_SIZE;
        elements = 0;
        hashNo = choice;
        collisions = 0;
        inAftExp = delAftShrink = 0;
        elmOflastExp = elmOflastShrink = 0;
        table.resize(Size);
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
            collisions++;

        table[index].push_back({key, value});
        elements++;
        inAftExp++;

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
                elements--;
                delAftShrink++;

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
struct blk
{
    K key;
    V value;
    int state = 0;
};

template <typename K, typename V>
class probeHash
{
    vector<blk<K, V>> table;
    vector<int> primaryCount;
    int Size, elements, hashNo;
    long long collisions;
    bool cstmHash;
    int inAftExp, delAftShrink;
    int elmOflastExp, elmOflastShrink;

    double loadFactor()
    {
        return (double)elements / Size;
    }

    int probeIndex(const K &key, int i)
    {
        long long h1 = primaryHash(key, Size, hashNo);
        long long h2 = auxiliaryHash(key, Size);

        if (!cstmHash)
            return (h1 + i * h2) % Size;

        return (h1 + C1 * i * h2 + C2 * 1LL * i * i) % Size;
    }

    bool place(const K &key, const V &value)
    {
        for (int i = 0; i < Size; i++)
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
        vector<blk<K, V>> oldTable = table;

        while (true)
        {
            Size = newSize;
            table.assign(Size, {});
            primaryCount.assign(Size, 0);

            bool successful = true;

            for (auto &blk : oldTable)
            {
                if (blk.state == 1 && !place(blk.key, blk.value))
                {
                    successful = false;
                    break;
                }
            }

            if (successful)
            {
                for (auto &blk : oldTable)
                    if (blk.state == 1)
                        primaryCount[primaryHash(blk.key, Size, hashNo)]++;

                return;
            }

            newSize = nextPrime(2 * newSize);
        }
    }

    void growNow()
    {
        resizeTable(nextPrime(2 * Size));

        elmOflastExp = elements;
        inAftExp = 0;

        if (elmOflastShrink == 0)
        {
            elmOflastShrink = elements;
            delAftShrink = 0;
        }
    }

    void checkGrow()
    {
        if (loadFactor() > MAX_LOAD && inAftExp >= elmOflastExp / 2)
            growNow();
    }

    void checkShrink()
    {
        if (Size > INIT_SIZE && loadFactor() < MIN_LOAD &&
            delAftShrink >= elmOflastShrink / 2)
        {
            resizeTable(previousPrime(Size / 2));
            elmOflastShrink = elements;
            delAftShrink = 0;
        }
    }

public:
    probeHash(int choice, bool useCstm)
    {
        Size = INIT_SIZE;
        elements = 0;
        hashNo = choice;
        cstmHash = useCstm;
        collisions = 0;
        inAftExp = delAftShrink = 0;
        elmOflastExp = elmOflastShrink = 0;

        table.resize(Size);
        primaryCount.assign(Size, 0);
    }

    void insert(const K &key, const V &value)
    {
        int firstDeleted = -1;

        for (int i = 0; i < Size; i++)
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
                    firstDeleted = index;
            }
            else
            {
                if (firstDeleted != -1)
                    index = firstDeleted;

                int home = primaryHash(key, Size, hashNo);

                if (primaryCount[home] > 0)
                    collisions++;

                primaryCount[home]++;

                table[index] = {key, value, 1};
                elements++;
                inAftExp++;

                checkGrow();
                return;
            }
        }

        if (firstDeleted != -1)
        {
            int home = primaryHash(key, Size, hashNo);

            if (primaryCount[home] > 0)
                collisions++;

            primaryCount[home]++;

            table[firstDeleted] = {key, value, 1};
            elements++;
            inAftExp++;

            checkGrow();
            return;
        }

        growNow();
        insert(key, value);
    }

    bool search(const K &key, V &value, int &hits)
    {
        hits = 0;

        for (int i = 0; i < Size; i++)
        {
            int index = probeIndex(key, i);

            if (table[index].state == 0)
                return false;

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
        for (int i = 0; i < Size; i++)
        {
            int index = probeIndex(key, i);

            if (table[index].state == 0)
                return false;

            if (table[index].state == 1 && table[index].key == key)
            {
                int home = primaryHash(key, Size, hashNo);

                primaryCount[home]--;
                table[index].state = 2;
                elements--;
                delAftShrink++;

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
        word += char('a' + rand() % 26);

    return word;
}

vector<string> genWords(int length)
{
    set<string> used;
    vector<string> words;

    while ((int)words.size() < TOTAL_KEYS)
    {
        string word = randomWord(length);

        if (used.insert(word).second)
            words.push_back(word);
    }

    return words;
}

template <typename Table>
pair<long long, double> testTable(Table &table, const vector<string> &words, const vector<int> &searchIndex)
{
    for (int i = 0; i < TOTAL_KEYS; i++)
        table.insert(words[i], i + 1);

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

    vector<string> wordsChaining = genWords(wordLength);
    vector<string> wordsDouble = genWords(wordLength);
    vector<string> wordsCustom = genWords(wordLength);

    vector<int> searchChaining(TO_SEARCHES);
    vector<int> searchDouble(TO_SEARCHES);
    vector<int> searchCustom(TO_SEARCHES);

    for (int i = 0; i < TO_SEARCHES; i++)
    {
        searchChaining[i] = rand() % TOTAL_KEYS;
        searchDouble[i] = rand() % TOTAL_KEYS;
        searchCustom[i] = rand() % TOTAL_KEYS;
    }

    long long collision[3][2];
    double hits[3][2];

    for (int hashNo = 1; hashNo <= 2; hashNo++)
    {
        ChainHash<string, int> chaining(hashNo);
        probeHash<string, int> doubleHashing(hashNo, false);
        probeHash<string, int> cstmHash(hashNo, true);

        pair<long long, double> a = testTable(chaining, wordsChaining, searchChaining);
        pair<long long, double> b = testTable(doubleHashing, wordsDouble, searchDouble);
        pair<long long, double> c = testTable(cstmHash, wordsCustom, searchCustom);

        collision[0][hashNo - 1] = a.first;
        hits[0][hashNo - 1] = a.second;

        collision[1][hashNo - 1] = b.first;
        hits[1][hashNo - 1] = b.second;

        collision[2][hashNo - 1] = c.first;
        hits[2][hashNo - 1] = c.second;
    }

    string method[3] = {"Chaining Method", "Double Hashing", "Custom Probing"};

    cout << left << setw(20) << "Method" << setw(20) << "Hash1 Collision" << setw(15) << "Hash1 Hits" << setw(20) << "Hash2 Collision" << setw(15) << "Hash2 Hits" << '\n';

    for (int i = 0; i < 3; i++)
        cout << left << setw(20) << method[i] << setw(20) << collision[i][0] << setw(15) << hits[i][0] << setw(20) << collision[i][1] << setw(15) << hits[i][1] << '\n';

    return 0;
}