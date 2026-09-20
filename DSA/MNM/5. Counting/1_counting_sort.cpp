#include <iostream>
#include <vector>
using namespace std;

/*
    Counting Sort
    -------------
    Works when:
    1. Elements are non-negative integers
    2. Maximum value is not too large

    Idea:
    - Count how many times each value appears
    - Convert count array into prefix sum array
    - Place elements into correct sorted positions
    - Traverse input from right to left to keep it STABLE
*/

void countingSort(vector<int> &A)
{
    int n = A.size();

    // Step 1: Find the maximum element
    int k = A[0];
    for (int i = 1; i < n; i++)
    {
        if (A[i] > k)
        {
            k = A[i];
        }
    }

    // B = output array
    vector<int> B(n);

    // C = counting array, size k+1 because values go from 0 to k
    vector<int> C(k + 1, 0);

    // Step 2: Count frequency of each value
    for (int j = 0; j < n; j++)
    {
        C[A[j]]++;
    }

    // Step 3: Prefix sum
    // Now C[i] = number of elements less than or equal to i
    for (int i = 1; i <= k; i++)
    {
        C[i] = C[i] + C[i - 1];
    }

    // Step 4: Build output array from right to left
    // This makes counting sort stable 
    for (int j = n - 1; j >= 0; j--)
    {
        B[C[A[j]] - 1] = A[j]; // place A[j] into correct sorted position
        C[A[j]]--;             // decrease count for duplicate handling
    }

    // Step 5: Copy sorted result back to original array
    for (int i = 0; i < n; i++)
    {
        A[i] = B[i];
    }
}

int main()
{
    // Example input
    vector<int> A = {4, 2, 2, 8, 3, 3, 1};

    cout << "Original array: ";
    for (int x : A)
    {
        cout << x << " ";
    }
    cout << endl;

    // Perform counting sort
    countingSort(A);

    cout << "Sorted array:   ";
    for (int x : A)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

/*
Example walkthrough:
--------------------
Input:
A = {4, 2, 2, 8, 3, 3, 1}

Step 1: Find max
k = 8

Step 2: Count frequencies
Value: 0 1 2 3 4 5 6 7 8
Count: 0 1 2 2 1 0 0 0 1

Step 3: Prefix sums
Value: 0 1 2 3 4 5 6 7 8
C    : 0 1 3 5 6 6 6 6 7

Meaning:
- 1 element <= 1
- 3 elements <= 2
- 5 elements <= 3
- 6 elements <= 4
- 7 elements <= 8

Step 4: Place from right to left
This ensures stable sorting

Final sorted array:
1 2 2 3 3 4 8

Time Complexity:
O(n + k)

Space Complexity:
O(n + k)
*/