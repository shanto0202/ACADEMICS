#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

class Node {
public:
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int value) {
        key = value;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

class AVLTree {
public:
    Node* root;

    AVLTree() {
        root = nullptr;
    }

    int height(Node* n) {
        if (n == nullptr) {
            return 0;
        }
        return n->height;
    }

    int balance(Node* n) {
        if (n == nullptr) {
            return 0;
        }
        return height(n->left) - height(n->right);
    }

    void updateHeight(Node* n) {
        n->height = 1 + max(height(n->left), height(n->right));
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* temp = x->right;

        x->right = y;
        y->left = temp;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* temp = y->left;

        y->left = x;
        x->right = temp;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balanceTree(Node* n) {
        if (n == nullptr) {
            return nullptr;
        }

        updateHeight(n);

        int b = balance(n);

        if (b > 1) {
            if (balance(n->left) < 0) {
                n->left = leftRotate(n->left);
            }
            return rightRotate(n);
        }

        if (b < -1) {
            if (balance(n->right) > 0) {
                n->right = rightRotate(n->right);
            }
            return leftRotate(n);
        }

        return n;
    }

    Node* insertNode(Node* n, int key, bool& inserted) {
        if (n == nullptr) {
            inserted = true;
            return new Node(key);
        }

        if (key < n->key) {
            n->left = insertNode(n->left, key, inserted);
        }
        else if (key > n->key) {
            n->right = insertNode(n->right, key, inserted);
        }
        else {
            return n;
        }

        return balanceTree(n);
    }

    Node* minimum(Node* n) {
        while (n != nullptr && n->left != nullptr) {
            n = n->left;
        }
        return n;
    }

    Node* deleteNode(Node* n, int key, bool& deleted) {
        if (n == nullptr) {
            return nullptr;
        }

        if (key < n->key) {
            n->left = deleteNode(n->left, key, deleted);
        }
        else if (key > n->key) {
            n->right = deleteNode(n->right, key, deleted);
        }
        else {
            deleted = true;

            if (n->left == nullptr || n->right == nullptr) {
                Node* child = (n->left != nullptr) ? n->left : n->right;
                delete n;
                return child;
            }

            Node* successor = minimum(n->right);
            n->key = successor->key;

            bool dummy = false;
            n->right = deleteNode(n->right, successor->key, dummy);
        }

        return balanceTree(n);
    }

    bool find(int key) {
        Node* current = root;

        while (current != nullptr) {
            if (key == current->key) {
                return true;
            }

            if (key < current->key) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        return false;
    }

    string treeString(Node* n) {
        if (n == nullptr) {
            return "";
        }

        string result = to_string(n->key);

        if (n->left != nullptr || n->right != nullptr) {
            result += "(";
            result += treeString(n->left);
            result += ",";
            result += treeString(n->right);
            result += ")";
        }

        return result;
    }

    void inorder(Node* n, vector<int>& result) {
        if (n == nullptr) {
            return;
        }

        inorder(n->left, result);
        result.push_back(n->key);
        inorder(n->right, result);
    }

    bool insert(int key) {
        bool inserted = false;
        root = insertNode(root, key, inserted);
        return inserted;
    }

    bool erase(int key) {
        bool deleted = false;
        root = deleteNode(root, key, deleted);
        return deleted;
    }

    vector<int> traverse() {
        vector<int> result;
        inorder(root, result);
        return result;
    }

    void clear(Node* n) {
        if (n == nullptr) {
            return;
        }

        clear(n->left);
        clear(n->right);
        delete n;
    }

    ~AVLTree() {
        clear(root);
    }
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        return 1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    if (!input || !output) {
        return 1;
    }

    AVLTree tree;

    long long insertTotal = 0;
    long long deleteTotal = 0;
    long long findTotal = 0;
    long long traverseTotal = 0;

    int insertCount = 0;
    int deleteCount = 0;
    int findCount = 0;
    int traverseCount = 0;

    string command;

    while (input >> command) {
        if (command == "I") {
            int value;
            input >> value;

            auto start = chrono::high_resolution_clock::now();
            bool ok = tree.insert(value);
            auto finish = chrono::high_resolution_clock::now();

            insertTotal += chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            insertCount++;

            if (ok) {
                output << tree.treeString(tree.root) << "\n";
            }
            else {
                output << "duplicate\n";
            }
        }

        else if (command == "D") {
            int value;
            input >> value;

            auto start = chrono::high_resolution_clock::now();
            bool ok = tree.erase(value);
            auto finish = chrono::high_resolution_clock::now();

            deleteTotal += chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            deleteCount++;

            if (ok) {
                output << tree.treeString(tree.root) << "\n";
            }
            else {
                output << "not found\n";
            }
        }

        else if (command == "F") {
            int value;
            input >> value;

            auto start = chrono::high_resolution_clock::now();
            bool ok = tree.find(value);
            auto finish = chrono::high_resolution_clock::now();

            findTotal += chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            findCount++;

            if (ok) {
                output << "found\n";
            }
            else {
                output << "not found\n";
            }
        }

        else if (command == "T") {
            auto start = chrono::high_resolution_clock::now();
            vector<int> result = tree.traverse();
            auto finish = chrono::high_resolution_clock::now();

            traverseTotal += chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            traverseCount++;

            for (int i = 0; i < (int)result.size(); i++) {
                if (i > 0) {
                    output << " ";
                }
                output << result[i];
            }

            output << "\n";
        }
    }

    cout << "operation,count,total_ns,average_ns\n";

    if (insertCount > 0) {
        cout << "insert," << insertCount << "," << insertTotal << "," << insertTotal / insertCount << "\n";
    }

    if (deleteCount > 0) {
        cout << "delete," << deleteCount << "," << deleteTotal << "," << deleteTotal / deleteCount << "\n";
    }

    if (findCount > 0) {
        cout << "find," << findCount << "," << findTotal << "," << findTotal / findCount << "\n";
    }

    if (traverseCount > 0) {
        cout << "traverse," << traverseCount << "," << traverseTotal << "," << traverseTotal / traverseCount << "\n";
    }

    return 0;
}