#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node
{
public:
    int key;
    int height;
    Node *left;
    Node *right;

    Node(int value)
    {
        key = value;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

class AVLTree
{
private:
    Node *root;

    int getHeight(Node *node) const
    {
        if (node != nullptr)
        {
            return node->height;
        }
        else
        {
            return 0;
        }
    }

    void updateHeight(Node *node)
    {
        if (node)
        {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }

    int getBF(Node *node) const
    {
        if (node == nullptr)
        {
            return 0;
        }

        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);

        return leftHeight - rightHeight;
    }

    Node *rotateRight(Node *y)
    {
        Node *x = y->left;
        Node *middle = x->right;

        x->right = y;
        y->left = middle;

        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node *rotateLeft(Node *x)
    {
        Node *y = x->right;
        Node *middle = y->left;

        y->left = x;
        x->right = middle;

        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node *rebalance(Node *node)
    {
        if (!node)
            return nullptr;

        updateHeight(node);
        int balance = getBF(node);

        if (balance > 1)
        {
            if (getBF(node->left) < 0)
            {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }

        if (balance < -1)
        {
            if (getBF(node->right) > 0)
            {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    Node *insertNode(Node *node, int key, bool &inserted)
    {
        if (!node)
        {
            inserted = true;
            return new Node(key);
        }

        if (key < node->key)
        {
            node->left = insertNode(node->left, key, inserted);
        }
        else if (key > node->key)
        {
            node->right = insertNode(node->right, key, inserted);
        }
        else
        {
            return node;
        }

        return rebalance(node);
    }

    Node *minimumNode(Node *node) const
    {
        while (node && node->left)
        {
            node = node->left;
        }
        return node;
    }

    Node *delNode(Node *node, int key, bool &erased)
    {
        if (!node)
            return nullptr;

        if (key < node->key)
        {
            node->left = delNode(node->left, key, erased);
        }
        else if (key > node->key)
        {
            node->right = delNode(node->right, key, erased);
        }
        else
        {
            erased = true;

            if (!node->left || !node->right)
            {
                Node *child = node->left ? node->left : node->right;
                delete node;
                return child;
            }

            Node *succ = minimumNode(node->right);
            node->key = succ->key;
            bool removedSuccessor = false;
            node->right = delNode(node->right, succ->key, removedSuccessor);
        }

        return rebalance(node);
    }

    bool findNode(Node *node, int key) const
    {
        while (node)
        {
            if (key == node->key)
                return true;
            node = (key < node->key) ? node->left : node->right;
        }
        return false;
    }

    void inorder(Node *node, vector<int> &result) const
    {
        if (!node)
            return;
        inorder(node->left, result);
        result.push_back(node->key);
        inorder(node->right, result);
    }

    string buildTreeString(Node *node) const
    {
        if (!node)
            return "";

        string result = to_string(node->key);
        if (node->left || node->right)
        {
            result += "(";
            result += buildTreeString(node->left);
            result += ",";
            result += buildTreeString(node->right);
            result += ")";
        }
        return result;
    }

    void clear(Node *node)
    {
        if (!node)
            return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree()
    {
        clear(root);
    }

    bool insert(int key)
    {
        bool inserted = false;
        root = insertNode(root, key, inserted);
        return inserted;
    }

    bool erase(int key)
    {
        bool erased = false;
        root = delNode(root, key, erased);
        return erased;
    }

    bool find(int key) const
    {
        return findNode(root, key);
    }

    vector<int> traverse() const
    {
        vector<int> result;
        inorder(root, result);
        return result;
    }

    string treeString() const
    {
        return buildTreeString(root);
    }
};

struct TimingData
{
    long long count = 0;
    long long totalNs = 0;
};

static void printTimingRow(ofstream &timing, const string &name, const TimingData &data)
{
    timing << name << "," << data.count << "," << data.totalNs << ",";

    if (data.count == 0)
        timing << "N/A\n";
    else
        timing << data.totalNs / data.count << "\n";
}
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <input-file> <output-file>\n";
        return 1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);
    ofstream timing("timing report.txt");
    if (!input || !output)
    {
        cerr << "Could not open input or output file.\n";
        return 1;
    }

    AVLTree tree;
    TimingData insertTiming, deleteTiming, findTiming, traverseTiming;

    string command;
    while (input >> command)
    {
        if (command == "I")
        {
            int key;
            input >> key;

            auto start = chrono::high_resolution_clock::now();
            bool inserted = tree.insert(key);
            auto stop = chrono::high_resolution_clock::now();

            insertTiming.count++;
            insertTiming.totalNs += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

            if (inserted)
                output << tree.treeString() << '\n';
            else
                output << "duplicate\n";
        }
        else if (command == "D")
        {
            int key;
            input >> key;

            auto start = chrono::high_resolution_clock::now();
            bool erased = tree.erase(key);
            auto stop = chrono::high_resolution_clock::now();

            deleteTiming.count++;
            deleteTiming.totalNs += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

            if (erased)
                output << tree.treeString() << '\n';
            else
                output << "not found\n";
        }
        else if (command == "F")
        {
            int key;
            input >> key;

            auto start = chrono::high_resolution_clock::now();
            bool found = tree.find(key);
            auto stop = chrono::high_resolution_clock::now();

            findTiming.count++;
            findTiming.totalNs += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

            output << (found ? "found" : "not found") << '\n';
        }
        else if (command == "T")
        {
            auto start = chrono::high_resolution_clock::now();
            vector<int> values = tree.traverse();
            auto stop = chrono::high_resolution_clock::now();

            traverseTiming.count++;
            traverseTiming.totalNs += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

            for (size_t i = 0; i < values.size(); ++i)
            {
                if (i)
                    output << ' ';
                output << values[i];
            }
            output << '\n';
        }
    }

    timing << "operation,count,total_ns,average_ns\n";

    printTimingRow(timing, "insert", insertTiming);
    printTimingRow(timing, "delete", deleteTiming);
    printTimingRow(timing, "find", findTiming);
    printTimingRow(timing, "traverse", traverseTiming);

    return 0;
}
