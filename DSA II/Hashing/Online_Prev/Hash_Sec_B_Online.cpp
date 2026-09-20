#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"
#define sajai(x) sort(x.begin(), x.end())
#define loop(i, j, n) for (ll i = j; i < n; i++)
const int N = 13;

struct Node
{
    string key;
    int value;
    double weight;
};

class ChainingHashTable
{
    list<Node> table[N];

public:
    // Position-weighted hash given in the question.
    int Hash1(const string &key)
    {
        int hashValue = 0;
        for (int i = 0; i < (int)key.size(); i++)
        {
            hashValue += (i + 1) * key[i];
        }
        return hashValue % N;
    }

    // Weight depends on the first and last characters.
    double weightCal(const string &key)
    {
        return ((key.front() + key.back()) % 100) / 100.0;
    }

    void insert(const string &key, int value)
    {
        int index = Hash1(key);
        auto &chain = table[index];

        // Discard a duplicate key.
        for (auto &node : chain)
        {
            if (node.key == key)
                return;
        }

        Node newNode = {key, value, weightCal(key)};
        auto it = chain.begin();

        // Skip all greater or equal weights, then insert here.
        // Using >= keeps an equal-weight older node before the new node.
        while (it != chain.end() && it->weight >= newNode.weight)
        {
            it++;
        }
        chain.insert(it, newNode);
    }

    void print()
    {
        cout << fixed << setprecision(2);
        for (int i = 0; i < N; i++)
        {
            cout << i << ": ";

            if (table[i].empty())
            {
                cout << "(empty)" << tata;
                continue;
            }

            bool first = true;
            for (auto &node : table[i])
            {
                if (!first)
                    cout << " -> ";
                cout << node.key << " (" << node.weight << ")";
                first = false;
            }
            cout << tata;
        }
    }
};

int main()
{
    ChainingHashTable hashTable;
    vector<string> words = {"cat", "dog", "bat", "rat", "sun", "fun", "run", "top", "pot", "opt", "art", "tar"};
    for (int i = 0; i < (int)words.size(); i++)
    {
        hashTable.insert(words[i], i + 1);
    }
    hashTable.print();
    return 0;
}