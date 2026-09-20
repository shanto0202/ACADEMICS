#include <iostream>
using namespace std;

struct Node
{
    int key;
    Node *l;
    Node *r;
};

/*
    Search in BST
*/
bool searchBST(Node *root, int x)
{
    if (root == NULL)
        return false;

    if (root->key == x)
        return true;

    if (x < root->key)
        return searchBST(root->l, x);
    else
        return searchBST(root->r, x);
}

/*
    Search in generalized binary tree
*/
bool searchBinaryTree(Node *root, int x)
{
    if (root == NULL)
        return false;

    if (root->key == x)
        return true;

    return searchBinaryTree(root->l, x) ||
           searchBinaryTree(root->r, x);
}

/*
Key Notes:

1. BST Search:
   Uses BST property:
   - left subtree contains smaller values
   - right subtree contains larger values

2. So for BST, at each node we search only one side.

3. Time Complexity of BST Search:
   O(h), where h = height of BST.

4. If BST is balanced:
   h = log n
   So time = O(log n).

5. If BST is skewed:
   h = n
   So time = O(n).

6. Generalized Binary Tree:
   No BST ordering property exists.

7. Therefore, we may need to search both left and right subtree.

8. Time Complexity of generalized binary tree search:
   O(n), because in worst case every node may be visited.

9. Space Complexity:
   O(h), due to recursive call stack.
*/