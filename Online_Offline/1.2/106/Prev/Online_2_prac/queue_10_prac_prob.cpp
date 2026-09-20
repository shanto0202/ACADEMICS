#include <bits/stdc++.h>
using namespace std;

// 1. Implementation using Linked List (Template)
template <typename T>
class MyQueue
{
    struct Node
    {
        T data;
        Node *next;
        Node(T val) : data(val), next(nullptr) {}
    };
    Node *frontNode, *rearNode;
    int qSize;

public:
    MyQueue() : frontNode(nullptr), rearNode(nullptr), qSize(0) {}

    void enqueue(T val)
    {
        Node *newNode = new Node(val);
        if (!rearNode)
        {
            frontNode = rearNode = newNode;
        }
        else
        {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        qSize++;
    }

    void dequeue()
    {
        if (!frontNode)
            return;
        Node *temp = frontNode;
        frontNode = frontNode->next;
        if (!frontNode)
            rearNode = nullptr;
        delete temp;
        qSize--;
    }

    T front() { return frontNode->data; }
    bool isEmpty() { return qSize == 0; }
    int size() { return qSize; }
};

// --- Problem Solutions ---

class QueueProblems
{
public:
    // 2. Circular Queue (Array-based logic)
    class CircularQueue
    {
        int *arr, front, rear, capacity, currSize;

    public:
        CircularQueue(int c) : capacity(c), front(0), rear(c - 1), currSize(0)
        {
            arr = new int[capacity];
        }
        bool enqueue(int x)
        {
            if (currSize == capacity)
                return false;
            rear = (rear + 1) % capacity;
            arr[rear] = x;
            currSize++;
            return true;
        }
        int dequeue()
        {
            if (currSize == 0)
                return -1;
            int res = arr[front];
            front = (front + 1) % capacity;
            currSize--;
            return res;
        }
    };

    // 4. Reverse a Queue using Recursion
    static void reverseQueue(queue<int> &q)
    {
        if (q.empty())
            return;
        int x = q.front();
        q.pop();
        reverseQueue(q);
        q.push(x);
    }

    // 5. Generate Binary Numbers 1 to N
    static vector<string> generateBinary(int n)
    {
        vector<string> res;
        queue<string> q;
        q.push("1");
        while (n--)
        {
            string curr = q.front();
            q.pop();
            res.push_back(curr);
            q.push(curr + "0");
            q.push(curr + "1");
        }
        return res;
    }

    // 6. Stack using Two Queues (Push costly)
    class StackUsingQueues
    {
        queue<int> q1, q2;

    public:
        void push(int x)
        {
            q2.push(x);
            while (!q1.empty())
            {
                q2.push(q1.front());
                q1.pop();
            }
            swap(q1, q2);
        }
        void pop() { q1.pop(); }
        int top() { return q1.front(); }
    };

    // 7. First non-repeating character in a stream
    static string firstNonRepeating(string A)
    {
        unordered_map<char, int> count;
        queue<char> q;
        string res = "";
        for (char ch : A)
        {
            count[ch]++;
            q.push(ch);
            while (!q.empty() && count[q.front()] > 1)
                q.pop();
            res += q.empty() ? '#' : q.front();
        }
        return res;
    }

    // 9. Sliding Window Maximum
    static vector<int> slidingWindowMax(vector<int> &nums, int k)
    {
        deque<int> dq;
        vector<int> res;
        for (int i = 0; i < nums.size(); i++)
        {
            if (!dq.empty() && dq.front() == i - k)
                dq.pop_front();
            while (!dq.empty() && nums[dq.back()] < nums[i])
                dq.pop_back();
            dq.push_back(i);
            if (i >= k - 1)
                res.push_back(nums[dq.front()]);
        }
        return res;
    }

    // 10. Rotten Oranges (BFS logic)
    static int orangesRotting(vector<vector<int>> &grid)
    {
        int n = grid.size(), m = grid[0].size(), fresh = 0, time = 0;
        queue<pair<int, int>> q;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == 2)
                    q.push({i, j});
                if (grid[i][j] == 1)
                    fresh++;
            }
        }
        int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
        while (!q.empty() && fresh > 0)
        {
            int sz = q.size();
            while (sz--)
            {
                pair<int, int> curr = q.front();
                q.pop();
                for (int i = 0; i < 4; i++)
                {
                    int nx = curr.first + dx[i], ny = curr.second + dy[i];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1)
                    {
                        grid[nx][ny] = 2;
                        fresh--;
                        q.push({nx, ny});
                    }
                }
            }
            time++;
        }
        return fresh == 0 ? time : -1;
    }
};