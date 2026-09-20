#include <iostream>
#include <vector>
using namespace std;

// Sort one bucket using insertion sort
// uniform distribution-> O(n)
// all elements go into one bucket-> O(n^2)
void insertionSort(vector<float> &b)
{
    for (int i = 1; i < b.size(); i++)
    {
        float key = b[i];
        int j = i - 1;

        while (j >= 0 && b[j] > key)
        {
            b[j + 1] = b[j];
            j--;
        }
        b[j + 1] = key;
    }
}

// Bucket sort for values in [0, 1)
void bucketSort(vector<float> &A)
{
    int n = A.size();
    // n can be anything
    vector<vector<float>> B(n); // create buckets

    // put elements into buckets
    for (int i = 0; i < n; i++)
        B[int(n * A[i])].push_back(A[i]); // 0.12*10=1.2 //int(1.2)=1 so 0.12 goes to bucket 1

    // sort each bucket
    for (int i = 0; i < n; i++)
        insertionSort(B[i]);

    // merge buckets back into A
    int k = 0;
    for (int i = 0; i < n; i++)
        for (float x : B[i])
            A[k++] = x;
}

int main()
{
    vector<float> A = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};

    bucketSort(A);

    for (float x : A)
        cout << x << " ";
}