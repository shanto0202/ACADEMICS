#include <bits/stdc++.h>
using namespace std;

int minNodes(int h)
{
    return h + 1;
}

int maxNodes(int h)
{
    return (1 << (h + 1)) - 1;
}

int main()
{
    int h;
    cin >> h;

    cout << "Minimum nodes = " << minNodes(h) << endl;
    cout << "Maximum nodes = " << maxNodes(h) << endl;

    return 0;
}

/*
Key Notes / Proof:

1. Height h means the longest path from root to leaf has h edges.

2. Minimum number of nodes:

   To get height h with minimum nodes, each level should contain
   only one node.

   Level 0 has 1 node
   Level 1 has 1 node
   Level 2 has 1 node
   ...
   Level h has 1 node

   Total nodes = 1 + 1 + 1 + ... + 1
               = h + 1

   Therefore,
   Minimum number of nodes = h + 1

--------------------------------------------------

3. Maximum number of nodes:

   To get maximum nodes, every level must be completely full.

   Level 0 has 1 node      = 2^0
   Level 1 has 2 nodes     = 2^1
   Level 2 has 4 nodes     = 2^2
   ...
   Level h has 2^h nodes

   Total nodes = 2^0 + 2^1 + 2^2 + ... + 2^h

   This is a geometric series.

   Sum = 2^(h+1) - 1

   Therefore,
   Maximum number of nodes = 2^(h+1) - 1

--------------------------------------------------

4. Final Answer:

   For a binary tree of height h:

   Minimum nodes = h + 1
   Maximum nodes = 2^(h+1) - 1
*/