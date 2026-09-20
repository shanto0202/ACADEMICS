#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int val;
    Node *l;
    Node *r;
};

// returns 1-indexed level order array
vector<int> levelOrderArray(Node *root)
{
    vector<int> arr;
    arr.push_back(0); // index 0 unused

    if (root == NULL)
        return arr;

    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *cur = q.front();
        q.pop();

        arr.push_back(cur->val);

        if (cur->l != NULL)
            q.push(cur->l);

        if (cur->r != NULL)
            q.push(cur->r);
    }

    return arr;
}

// access parent of node at index i
int getParent(vector<int> &arr, int i)
{
    if (i <= 1)
        return -1; // root has no parent

    return arr[i / 2];
}

int main()
{
    vector<int> arr = {0, 3, 9, 5, 14, 10, 6, 8, 17, 15, 13, 23, 12};

    cout << "Index of node 12 = 12" << endl;
    cout << "Parent of node 12 = " << getParent(arr, 12) << endl;

    return 0;
}

/*
Key Notes:

1. Use level-order traversal to store the tree in array.

2. For 1-indexed array:
   left child  = 2 * i
   right child = 2 * i + 1
   parent      = i / 2

3. Array placement:

   Index:  1  2  3  4   5   6  7  8   9   10  11  12
   Value:  3  9  5  14  10  6  8  17  15  13  23  12

4. Node 12 is at index 12.

5. Parent index of node 12:
   12 / 2 = 6

   arr[6] = 6

6. Therefore, parent of node 12 is 6.

7. Traversal Time Complexity:
   O(n)

8. Parent Access Time Complexity:
   O(1)
*/