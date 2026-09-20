#include <iostream>
#include <vector>
using namespace std;

const int N = 100;
int component[N];
int sz[N];
vector<int> members[N];

//overall O(k log(k))

// MakeSet(n)
void makeSet(int n)
{
    for (int i = 1; i <= n; i++)
    {
        component[i] = i;        // each node starts in its own set
        sz[i] = 1;               // size of each set = 1
        members[i].push_back(i); // store members of that set
    }
}

// Find(x) = O(1)
int findSet(int x)
{
    return component[x];
}

// Union(x, y)
void unionSet(int x, int y)
{
    int cx = findSet(x);
    int cy = findSet(y);

    if (cx == cy)
        return; // already same set

    // always merge smaller set into larger set
    if (sz[cx] < sz[cy])
        swap(cx, cy);

    // update all elements of smaller set
    for (int v : members[cy])
    {
        component[v] = cx;
        members[cx].push_back(v);
    }
    sz[cx] += sz[cy];
    members[cy].clear();
}

int main()
{
    int n = 8;
    makeSet(n);

    unionSet(1, 2);
    unionSet(3, 4);
    unionSet(1, 3);
    unionSet(5, 6);
    unionSet(7, 8);
    unionSet(5, 7);
    unionSet(1, 5);

    for (int i = 1; i <= n; i++)
    {
        cout << "Element " << i << " -> Component " << findSet(i) << endl;
    }

    return 0;
}

/*
Key Notes:

1. component[i]:
   - Stores which set element i belongs to.

2. members[c]:
   - Stores all members of component c.

3. findSet(x):
   - Just returns component[x]
   - Time = O(1)

4. unionSet(x, y):
   - Merge smaller set into larger set
   - Update component[] only for smaller set members

5. Why O(k log k)?
   - Whenever an element changes component,
     it moves to a set at least twice as large.
   - So one element can change sets at most log k times.
   - Across k unions, total work = O(k log k)

6. This is NOT the tree/path-compression DSU.
   - This is the older component-array style DSU.

7. Good for understanding the slide proof.
   - Not the fastest practical DSU.
*/