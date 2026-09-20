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

    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int balance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    void updateHeight(Node* node) {
        node->height = 1 + max(height(node->left), height(node->right));
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

    Node* balanceTree(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        updateHeight(node);

        int b = balance(node);

        if (b > 1) {
            if (balance(node->left) < 0) {
                node->left = leftRotate(node->left);
            }
            return rightRotate(node);
        }

        if (b < -1) {
            if (balance(node->right) > 0) {
                node->right = rightRotate(node->right);
            }
            return leftRotate(node);
        }

        return node;
    }

    Node* insertNode(Node* node, int key, bool& inserted) {
        if (node == nullptr) {
            inserted = true;
            return new Node(key);
        }

        if (key < node->key) {
            node->left = insertNode(node->left, key, inserted);
        }
        else if (key > node->key) {
            node->right = insertNode(node->right, key, inserted);
        }
        else {
            return node;
        }

        return balanceTree(node);
    }

    Node* minimum(Node* node) {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* deleteNode(Node* node, int key, bool& deleted) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = deleteNode(node->left, key, deleted);
        }
        else if (key > node->key) {
            node->right = deleteNode(node->right, key, deleted);
        }
        else {
            deleted = true;

            if (node->left == nullptr || node->right == nullptr) {
                Node* child = (node->left != nullptr) ? node->left : node->right;
                delete node;
                return child;
            }

            Node* successor = minimum(node->right);
            node->key = successor->key;

            bool dummy = false;
            node->right = deleteNode(node->right, successor->key, dummy);
        }

        return balanceTree(node);
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

    string treeString(Node* node) {
        if (node == nullptr) {
            return "";
        }

        string result = to_string(node->key);

        if (node->left != nullptr || node->right != nullptr) {
            result += "(";
            result += treeString(node->left);
            result += ",";
            result += treeString(node->right);
            result += ")";
        }

        return result;
    }

    void inorder(Node* node, vector<int>& result) {
        if (node == nullptr) {
            return;
        }

        inorder(node->left, result);
        result.push_back(node->key);
        inorder(node->right, result);
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

    void clear(Node* node) {
        if (node == nullptr) {
            return;
        }

        clear(node->left);
        clear(node->right);
        delete node;
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