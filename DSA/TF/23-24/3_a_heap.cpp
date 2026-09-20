#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000;

int Hmin[MAX], Hmax[MAX];
int posMin[MAX], posMax[MAX];
int heapSize = 0;

/* ---------- swap with position update ---------- */

void swapMin(int i, int j)
{
    swap(Hmin[i], Hmin[j]);
    posMin[Hmin[i]] = i;
    posMin[Hmin[j]] = j;
}

void swapMax(int i, int j)
{
    swap(Hmax[i], Hmax[j]);
    posMax[Hmax[i]] = i;
    posMax[Hmax[j]] = j;
}

/* ---------- heapify down ---------- */

void minHeapify(int i)
{
    int left = 2 * i;
    int right = 2 * i + 1;
    int smallest = i;

    if (left <= heapSize && Hmin[left] < Hmin[smallest])
        smallest = left;

    if (right <= heapSize && Hmin[right] < Hmin[smallest])
        smallest = right;

    if (smallest != i)
    {
        swapMin(i, smallest);
        minHeapify(smallest);
    }
}

void maxHeapify(int i)
{
    int left = 2 * i;
    int right = 2 * i + 1;
    int largest = i;

    if (left <= heapSize && Hmax[left] > Hmax[largest])
        largest = left;

    if (right <= heapSize && Hmax[right] > Hmax[largest])
        largest = right;

    if (largest != i)
    {
        swapMax(i, largest);
        maxHeapify(largest);
    }
}

/* ---------- heapify up ---------- */

void minHeapifyUp(int i)
{
    while (i > 1 && Hmin[i] < Hmin[i / 2])
    {
        swapMin(i, i / 2);
        i = i / 2;
    }
}

void maxHeapifyUp(int i)
{
    while (i > 1 && Hmax[i] > Hmax[i / 2])
    {
        swapMax(i, i / 2);
        i = i / 2;
    }
}

/* ---------- operations ---------- */

void insertValue(int x)
{
    heapSize++;

    Hmin[heapSize] = x;
    Hmax[heapSize] = x;

    posMin[x] = heapSize;
    posMax[x] = heapSize;

    minHeapifyUp(heapSize);
    maxHeapifyUp(heapSize);
}

int findMin()
{
    return Hmin[1];
}

int findMax()
{
    return Hmax[1];
}

void deleteFromMin(int i)
{
    swapMin(i, heapSize);
    heapSize--;

    if (i <= heapSize)
    {
        minHeapifyUp(i);
        minHeapify(i);
    }
}

void deleteFromMax(int i)
{
    swapMax(i, heapSize);
    heapSize--;

    if (i <= heapSize)
    {
        maxHeapifyUp(i);
        maxHeapify(i);
    }
}

void deleteMin()
{
    int x = Hmin[1];
    int p = posMax[x];

    deleteFromMin(posMin[x]);
    deleteFromMax(p);
}

void deleteMax()
{
    int x = Hmax[1];
    int p = posMin[x];

    deleteFromMax(posMax[x]);
    deleteFromMin(p);
}

int main()
{
    insertValue(10);
    insertValue(20);
    insertValue(5);
    insertValue(30);

    cout << "Minimum = " << findMin() << endl;
    cout << "Maximum = " << findMax() << endl;

    deleteMin();
    cout << "After deleteMin, Minimum = " << findMin() << endl;

    deleteMax();
    cout << "After deleteMax, Maximum = " << findMax() << endl;

    return 0;
}

/*
Key Notes:
Maintain the same set of numbers in two heaps.

1. Max-Heap Hmax:
   Root contains maximum.

2. Min-Heap Hmin:
   Root contains minimum.

Each element stores its position in both heaps.
This cross-position is the mutual dependency.

Operations:

findMax():
    return Hmax[1]
    Time = O(1)

findMin():
    return Hmin[1]
    Time = O(1)

insert(x):
    insert x into Hmax
    insert x into Hmin
    update positions in both heaps
    Time = O(log n)

deleteMax():
    x = Hmax[1]
    p = position of x in Hmin

    delete root from Hmax
    delete x from Hmin using position p

    Time = O(log n)

deleteMin():
    x = Hmin[1]
    p = position of x in Hmax

    delete root from Hmin
    delete x from Hmax using position p

    Time = O(log n)
    Complexity:

findMin  = O(1)
findMax  = O(1)
insert   = O(log n)
deleteMin = O(log n)
deleteMax = O(log n)

Space Complexity = O(n)
*/