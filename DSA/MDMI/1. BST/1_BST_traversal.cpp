#include <bits/stdc++.h>
using namespace std;
#define tata "\n"

// Definition of a node in the binary tree
struct Node
{
    int data;
    struct Node *l;
    struct Node *r;
};

// Global pointer to the root of the tree
struct Node *root = nullptr;

// Function to create a new node with a given value
Node *createNode(int val)
{
    Node *newNode = new Node();
    newNode->data = val;
    newNode->l = newNode->r = nullptr;
    return newNode;
}

// 1. Preorder Traversal: Root -> Left -> Right
void preorder(struct Node *rt)
{
    if (rt == nullptr)
        return;
    cout << rt->data << " "; // Visit root
    preorder(rt->l);      // Traverse left subtree
    preorder(rt->r);     // Traverse right subtree
}

// 2. Inorder Traversal: Left -> Root -> Right
void inorder(struct Node *rt)
{
    if (rt == nullptr)
        return;
    inorder(rt->l);       // Traverse left subtree
    cout << rt->data << " "; // Visit root
    inorder(rt->r);      // Traverse right subtree
}

// 3. Postorder Traversal: Left -> Right -> Root
void postorder(struct Node *rt)
{
    if (rt == nullptr)
        return;
    postorder(rt->l);     // Traverse left subtree
    postorder(rt->r);    // Traverse right subtree
    cout << rt->data << " "; // Visit root
}

// 4. Level Order Traversal: Visit nodes level by level from left to right
void levelOrder(struct Node *rt)
{
    if (rt == nullptr)
        return;
    queue<Node *> q; // Queue to hold nodes at each level
    q.push(rt);      // Start with the root node

    while (!q.empty())
    {
        Node *current = q.front();
        q.pop();

        cout << current->data << " "; // Visit current node

        // Enqueue left child first to maintain left-to-right order
        if (current->l != nullptr)
            q.push(current->l);
        // Enqueue right child
        if (current->r != nullptr)
            q.push(current->r);
    }
}
// --- Array-based Logic for Complete Binary Tree ---
int getParent(int i)
{
    return floor(i / 2); // floor ( (i - 1) / 2 ) for 0 based indexing
}
int getLeftChild(int i)
{
    return 2 * i;
}
int getRightChild(int i)
{
    return 2 * i + 1;
}

int main()
{
    // Build the following sample tree:
    //         1
    //        / \
    //       2   3
    //      / \
    //     4   5
    root = createNode(1);
    root->l = createNode(2);
    root->r = createNode(3);
    root->l->l = createNode(4);
    root->l->r = createNode(5);

    // Demonstrate all traversals
    cout << "Preorder   : ";
    preorder(root);
    cout << tata;
    cout << "Inorder    : ";
    inorder(root);
    cout << tata;
    cout << "Postorder  : ";
    postorder(root);
    cout << tata;
    cout << "Level Order: ";
    levelOrder(root);
    cout << tata;

    return 0;
}