#include <bits/stdc++.h>
using namespace std;
#define tata "\n"

struct Node
{
    int data;            // Value stored in the node
    struct Node *l;   // Pointer to left child
    struct Node *r;  // Pointer to right child
    struct Node *parent; // Pointer to parent node
};

// --- BST Operations (O(h) Complexity) ---

// 1. Search for a node with key k in the BST rooted at x
Node *treeSearch(Node *x, int k)
{
    if (x == nullptr || k == x->data)
        return x; // Return node if found or nullptr if not found
    if (k < x->data)
        return treeSearch(x->l, k); // Search left subtree
    else
        return treeSearch(x->r, k); // Search right subtree
}

// 2. Find the node with the minimum key in the BST rooted at x
Node *treeMinimum(Node *x)
{
    while (x->l != nullptr)
        x = x->l; // Go as left as possible
    return x;
}

// 3. Find the node with the maximum key in the BST rooted at x
Node *treeMaximum(Node *x)
{
    while (x->r != nullptr)
        x = x->r; // Go as right as possible
    return x;
}

// 4. Find the successor of node x (the node with the next higher key)
Node *treeSuccessor(Node *x)
{
    if (x->r != nullptr)
        return treeMinimum(x->r); // Successor is leftmost node in right subtree
    Node *y = x->parent;
    // Go up until we find a node that is a left child; its parent is the successor
    while (y != nullptr && x == y->r)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

// 5. Find the predecessor of node x (the node with the next lower key)
Node *treePredecessor(Node *x)
{
    if (x->l != nullptr)
        return treeMaximum(x->l); // Predecessor is rightmost node in left subtree
    Node *y = x->parent;
    // Go up until we find a node that is a right child; its parent is the predecessor
    while (y != nullptr && x == y->l)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

// 6. Insert a new node with key k into the BST
void treeInsert(Node *&root, int k)
{
    Node *z = new Node{k, nullptr, nullptr, nullptr}; // New node to insert
    Node *y = nullptr;                                // Parent of x
    Node *x = root;                                   // Start from root

    // Find the correct position for the new node
    while (x != nullptr)
    {
        y = x;
        if (z->data < x->data)
            x = x->l;
        else
            x = x->r;
    }

    z->parent = y; // Set parent pointer
    if (y == nullptr)
        root = z; // Tree was empty, new node is root
    else if (z->data < y->data)
        y->l = z; // Insert as left child
    else
        y->r = z; // Insert as right child
}

void inorder(Node *root)
{
    if (root == nullptr)
        return;
    inorder(root->l);
    cout << root->data << " ";
    inorder(root->r);
}

// 7. Delete a node z from the BST (Implements logic from slides)
void deleteNode(Node *&root, Node *z)
{
    if (z == nullptr)
        return;

    // CASE 3: Node has TWO children
    // Strategy: Find successor, copy key, delete successor
    if (z->l != nullptr && z->r != nullptr)
    {
        // 1. Find successor (minimum in right subtree)
        Node *y = treeMinimum(z->r);

        // 2. Copy successor's key to node z
        z->data = y->data;

        // 3. Delete successor (Recursively call delete on the successor node)
        // The successor is guaranteed to have 0 or 1 child.
        deleteNode(root, y);
    }
    else
    {
        // CASE 1 & 2: Leaf node OR One child
        // Find the child (if any). If leaf, child will be nullptr.
        Node *child = (z->l != nullptr) ? z->l : z->r;

        // Update the child's parent pointer (if child exists)
        if (child != nullptr)
        {
            child->parent = z->parent;
        }
        // Update the parent's child pointer
        if (z->parent == nullptr)
        {
            // z was the root
            root = child;
        }
        else if (z == z->parent->l)
        {
            // z was a left child
            z->parent->l = child;
        }
        else
        {
            // z was a right child
            z->parent->r = child;
        }

        // Free memory
        delete z;
    }
}

// --- Main Function ---

int main()
{
    Node *root = nullptr;

    // Inserting keys to build the BST
    int keys[] = {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
    for (int k : keys)
    {
        treeInsert(root, k);
    }

    // --- Original Tests ---
    cout << "--- Original Tests ---" << endl;

    // Test searching for a node
    Node *found = treeSearch(root, 13);
    if (found)
        cout << "Search Found: " << found->data << endl;

    // Test finding minimum and maximum
    cout << "Tree Minimum: " << treeMinimum(root)->data << endl;
    cout << "Tree Maximum: " << treeMaximum(root)->data << endl;

    // Test finding the successor of 13
    Node *succ = treeSuccessor(found);
    if (succ)
        cout << "Successor of 13: " << succ->data << endl;

    // Test finding the predecessor of 6
    Node *node6 = treeSearch(root, 6);
    Node *pred = treePredecessor(node6);
    if (pred)
        cout << "Predecessor of 6: " << pred->data << endl;

    // --- Deletion Tests (From Slides) ---
    cout << tata << "--- Deletion Tests ---" << endl;
    cout << "Initial Inorder: ";
    inorder(root);
    cout << endl;

    // 1. Delete Leaf (e.g., 9)
    cout << "Deleting 9 (Leaf)..." << endl;
    deleteNode(root, treeSearch(root, 9));
    cout << "Inorder: ";
    inorder(root);
    cout << endl;

    // 2. Delete Node with One Child (e.g., 7)
    // Note: In original tree, 7 had child 13 (which had child 9).
    // After deleting 9, 7 still has child 13.
    cout << "Deleting 7 (Has one child)..." << endl;
    deleteNode(root, treeSearch(root, 7));
    cout << "Inorder: ";
    inorder(root);
    cout << endl;
    // 3. Delete Node with Two Children (e.g., 6)
    // 6 has children 3 and (the subtree starting at 13).
    cout << "Deleting 6 (Two children)..." << endl;
    deleteNode(root, treeSearch(root, 6));
    cout << "Inorder: ";
    inorder(root);
    cout << endl;
    return 0;
}