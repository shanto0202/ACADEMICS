#include <bits/stdc++.h>
using namespace std;

void reverseFirstK(queue<int> &q, int k)
{
    stack<int> st;

    // Step 1: push first k elements into stack
    for (int i = 0; i < k; i++)
    {
        st.push(q.front());
        q.pop();
    }

    // Step 2: push back stack elements (reversed)
    while (!st.empty())
    {
        q.push(st.top());
        st.pop();
    }

    // Step 3: move remaining (n-k) elements to back
    int n = q.size();
    for (int i = 0; i < n - k; i++)
    {
        q.push(q.front());
        q.pop();
    }
}

int main()
{
    queue<int> q;
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};

    for (int x : arr)
        q.push(x);

    int k = 4;

    reverseFirstK(q, k);

    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }

    return 0;
}

/*
Key Notes:

1. Use a stack to reverse order (LIFO).

2. Steps:
   - Remove first k elements → push into stack
   - Pop stack → enqueue (reversed order)
   - Move remaining elements to maintain order

3. Example:
   Input:  [10 20 30 40 50 60 70 80 90]
   Output: [40 30 20 10 50 60 70 80 90]

4. Time Complexity:
   O(n)

5. Space Complexity:
   O(k)
*/