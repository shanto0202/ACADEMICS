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
    unsigned long long value = 0;
    int base = (hashNo == 1 ? 31 : 37);
    for (unsigned char ch : key) value = value * base + ch;
    return value % Size;
}

int auxiliaryHash(const string &key, int Size)
{
    unsigned long long value = 0;
    for (unsigned char ch : key) value = value * 41 + ch;
    return 1 + value % (Size - 1);
}

// state: 0 = never used, 1 = occupied, 2 = deleted
// ====================== STRUCTURE CHANGE AREA =====================
template <typename K, typename V>
struct blk
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
    while (n > INIT_SIZE && !isPrime(n)) n--;
    return max(n, INIT_SIZE);
}

template <typename K, typename V>
class probeHash
{
    vector<blk<K, V>> table;
    int Size, elements, hashNo;
    long long collisions;

    double loadFactor() const { return (double)elements / Size; }

    // ====================== PROBE CHANGE AREA ======================
    int probeIndex(const K &key, int i) const
    {
        int h1 = primaryHash(key, Size, hashNo);
        int h2 = auxiliaryHash(key, Size);
        return (h1 + 1LL * i * h2) % Size;
    }

    bool placeWithoutCounting(const K &key, const V &value)
    {
        for (int i = 0; i < Size; i++)
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
            Size = newSize;
            table.assign(Size, {});
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
        if (loadFactor() > MAX_LOAD)
            resizeTable(nextPrime(2 * Size));
    }

    void checkShrink()
    {
        if (Size > INIT_SIZE && loadFactor() < MIN_LOAD)
            resizeTable(previousPrime(Size / 2));
    }

public:
    probeHash(int choice = 1)
    {
        Size = INIT_SIZE;
        elements = 0;
        hashNo = choice;
        collisions = 0;
        table.resize(Size);
    }

    void insert(const K &key, const V &value)
    {
        int firstDeleted = -1;

        // ===================== INSERT CHANGE AREA =====================
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

        resizeTable(nextPrime(2 * Size));
        insert(key, value);
    }

    bool search(const K &key, V &value, int &hits) const
    {
        hits = 0;
        for (int i = 0; i < Size; i++)
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

    bool deleteKey(const K &key)
    {
        for (int i = 0; i < Size; i++)
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
        for (int i = 0; i < Size; i++)
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
        probeHash<string, int> doubleHashing(hashNo);
        auto result = testTable(doubleHashing, words, searchIndex);
        collision[hashNo - 1] = result.first;
        hits[hashNo - 1] = result.second;
    }
    cout << left << setw(20) << "Method" << setw(20) << "Hash1 Collision"
         << setw(15) << "Hash1 Hits" << setw(20) << "Hash2 Collision"
         << setw(15) << "Hash2 Hits" << '\n';
    cout << left << setw(20) << "Double Hashing" << setw(20) << collision[0]
         << setw(15) << hits[0] << setw(20) << collision[1] << setw(15) << hits[1] << '\n';
    return 0;
}
