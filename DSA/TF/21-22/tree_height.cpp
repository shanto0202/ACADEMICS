#include <iostream>
using namespace std;

int findHeight(int parent[], int n)
{
    int height = 0;

    // Traverse each node
    for (int i = 0; i < n; i++) 
    {
        int depth = 0;
        int current = i;

        // Move towards root
        while (parent[current] != -1)
        {
            current = parent[current];
            depth++;
        }

        // Update maximum depth
        if (depth > height)
            height = depth;
    }

    return height;
}

int main()
{
    int parent[] = {-1, 0, 0, 0, 3, 1, 1, 2};
    int n = 8;

    cout << "Height of tree = " << findHeight(parent, n) << endl;

    return 0;
}

/*
Key Notes:

1. parent[i] stores the immediate parent of node i.

2. Root node is identified by parent[i] = -1.

3. Depth of a node:
   Number of edges from root to that node.

4. Height of tree:
   Maximum depth among all nodes.

5. Idea:
   - For each node, follow parent[] until reaching root.
   - Count how many steps (depth).
   - Take the maximum.

6. Time Complexity:
   O(n^2) in worst case (skewed tree).

7. Space Complexity:
   O(1), no extra memory used.

8. Optimization (important in exams):
   Use DP/memoization to store depth → reduces to O(n).
*/