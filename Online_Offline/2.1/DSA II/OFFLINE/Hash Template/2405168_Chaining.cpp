#include <bits/stdc++.h>
using namespace std;

const int INIT_SIZE = 13;
const double MAX_LOAD = 0.50;
const double MIN_LOAD = 0.25;
const int TOTAL_KEYS = 10000;
const int TO_SEARCHES = 1000;

string keyString(char key) { return string(1, key); }
string keyString(const string &key) { return key; }

template <typename K>
string keyString(const K &key) { return to_string(key); }

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

bool isPrime(int n)
{
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int nextPrime(int n)
{
    n++;
    while (!isPrime(n)) n++;
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
    vector<list<pair<K, V>>> table;
    int Size, elements, hashNo;
    long long collisions;
    int inAftExp, delAftShrink;
    int elmOflastExp, elmOflastShrink;

    double loadFactor() { return (double)elements / Size; }
    int indexOf(const K &key) { return primaryHash(key, Size, hashNo); }

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

        if (!table[index].empty()) collisions++;
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

    long long getCollisions() { return collisions; }
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
        if (used.insert(word).second) words.push_back(word);
    }
    return words;
}

template <typename Table>
pair<long long, double> testTable(Table &table, const vector<string> &words,
                                  const vector<int> &searchIndex)
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
    vector<string> words = genWords(wordLength);
    vector<int> searchIndex(TO_SEARCHES);

    for (int i = 0; i < TO_SEARCHES; i++)
        searchIndex[i] = rand() % TOTAL_KEYS;

    long long collision[2];
    double hits[2];

    for (int hashNo = 1; hashNo <= 2; hashNo++)
    {
        ChainHash<string, int> chaining(hashNo);
        auto result = testTable(chaining, words, searchIndex);
        collision[hashNo - 1] = result.first;
        hits[hashNo - 1] = result.second;
    }

    cout << left << setw(20) << "Method"
         << setw(20) << "Hash1 Collision"
         << setw(15) << "Hash1 Hits"
         << setw(20) << "Hash2 Collision"
         << setw(15) << "Hash2 Hits" << '\n';

    cout << left << setw(20) << "Chaining Method"
         << setw(20) << collision[0] << setw(15) << hits[0]
         << setw(20) << collision[1] << setw(15) << hits[1] << '\n';

    return 0;
}
