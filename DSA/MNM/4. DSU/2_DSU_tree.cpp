#include <iostream>
using namespace std;

const int N = 100;
int parent[N];
int sz[N];

// O(kα(n))

//  MakeUnionFind(n)
void makeSet(int n)
{
    for (int i = 1; i <= n; i++)
    {
        parent[i] = i; // initially নিজের parent নিজেই
        sz[i] = 1;     // initially each set size = 1
    }
}

// O(log(n))
//  find(x) with path compression
int findSet(int x)
{
    if (parent[x] == x)
        return x;

    return parent[x] = findSet(parent[x]); // path compression
}

// O(log(n))
//  Union(x, y) using size
void unionSet(int x, int y)
{
    int rx = findSet(x); // rx=3
    int ry = findSet(y); // ry=8

    if (rx == ry)
        return; // already in same set

    // smaller set goes under larger set
    if (sz[rx] < sz[ry])
        swap(rx, ry); // rx=8, ry=3

    parent[ry] = rx;
    sz[rx] += sz[ry];
}

int main()
{
    int n = 7;
    makeSet(n);

    unionSet(1, 2);
    unionSet(2, 3);
    unionSet(4, 5);
    unionSet(6, 7);
    unionSet(5, 6);

    cout << "Representative of 3: " << findSet(3) << endl;
    cout << "Representative of 7: " << findSet(7) << endl;

    if (findSet(3) == findSet(7))
        cout << "3 and 7 are in the same set" << endl;
    else
        cout << "3 and 7 are in different sets" << endl;

    unionSet(3, 7);

    if (findSet(3) == findSet(7))
        cout << "After union, 3 and 7 are in the same set" << endl;
    else
        cout << "After union, 3 and 7 are in different sets" << endl;

    return 0;
}

/*
Key Notes:

1. makeSet(n):
   - Initially every node is its own parent.
   - Means every element starts in a separate set.

2. findSet(x):
   - Finds the representative/root of x.
   - If two elements have same representative, they are in same set.

3. Path Compression:
   - parent[x] = findSet(parent[x])
   - Makes future find operations faster.

4. unionSet(x, y):
   - First find roots of x and y.
   - If roots are different, merge them.

5. Union by Size:
   - Smaller tree goes under bigger tree.
   - Keeps tree short, so operations become faster.

6. Time Complexity:
   - Very fast in practice.
   - With path compression + union by size, almost constant time.

7. Main Use:
   - Detect cycle
   - Kruskal’s MST
   - Check connectivity
   - Group elements into disjoint sets
*/