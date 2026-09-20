#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

// 1. Implementation using Linked List (Template)
template <typename T>
class Stack
{
    struct Node
    {
        T data;
        Node *next;
        Node(T val) : data(val), next(nullptr) {}
    };
    Node *topNode;
    int stackSize;

public:
    Stack() : topNode(nullptr), stackSize(0) {}

    void push(T val)
    {
        Node *newNode = new Node(val);
        newNode->next = topNode;
        topNode = newNode;
        stackSize++;
    }

    void pop()
    {
        if (!topNode)
            return;
        Node *temp = topNode;
        topNode = topNode->next;
        delete temp;
        stackSize--;
    }

    T top() { return topNode->data; }
    bool isEmpty() { return topNode == nullptr; }
    int size() { return stackSize; }
};

// --- Problem Solutions ---

class StackProblems
{
public:
    // 2. Evaluate Postfix
    static int evaluatePostfix(string exp)
    {
        stack<int> s;
        for (char c : exp)
        {
            if (isdigit(c))
                s.push(c - '0');
            else
            {
                int v2 = s.top();
                s.pop();
                int v1 = s.top();
                s.pop();
                if (c == '+')
                    s.push(v1 + v2);
                else if (c == '-')
                    s.push(v1 - v2);
                else if (c == '*')
                    s.push(v1 * v2);
                else if (c == '/')
                    s.push(v1 / v2);
            }
        }
        return s.top();
    }

    // 3. Infix to Postfix
    static int prec(char c)
    {
        if (c == '^')
            return 3;
        if (c == '*' || c == '/')
            return 2;
        if (c == '+' || c == '-')
            return 1;
        return -1;
    }

    static string infixToPostfix(string s)
    {
        stack<char> st;
        string res;
        for (char c : s)
        {
            if (isalnum(c))
                res += c;
            else if (c == '(')
                st.push('(');
            else if (c == ')')
            {
                while (st.top() != '(')
                {
                    res += st.top();
                    st.pop();
                }
                st.pop();
            }
            else
            {
                while (!st.empty() && prec(c) <= prec(st.top()))
                {
                    res += st.top();
                    st.pop();
                }
                st.push(c);
            }
        }
        while (!st.empty())
        {
            res += st.top();
            st.pop();
        }
        return res;
    }

    // 4. Next Greater Element
    static vector<int> nextGreater(vector<int> arr)
    {
        int n = arr.size();
        vector<int> res(n, -1);
        stack<int> s;
        for (int i = n - 1; i >= 0; i--)
        {
            while (!s.empty() && s.top() <= arr[i])
                s.pop();
            if (!s.empty())
                res[i] = s.top();
            s.push(arr[i]);
        }
        return res;
    }

    // 5. Stock Span
    static vector<int> stockSpan(vector<int> price)
    {
        int n = price.size();
        vector<int> span(n);
        stack<int> s; // stores indices
        for (int i = 0; i < n; i++)
        {
            while (!s.empty() && price[s.top()] <= price[i])
                s.pop();
            span[i] = s.empty() ? (i + 1) : (i - s.top());
            s.push(i);
        }
        return span;
    }

    // 6. MinStack (O(1) GetMin)
    class MinStack
    {
        stack<int> s, minS;

    public:
        void push(int x)
        {
            s.push(x);
            if (minS.empty() || x <= minS.top())
                minS.push(x);
        }
        void pop()
        {
            if (s.top() == minS.top())
                minS.pop();
            s.pop();
        }
        int getMin() { return minS.top(); }
    };

    // 7. Balanced Parentheses
    static bool isValid(string str)
    {
        stack<char> s;
        for (char c : str)
        {
            if (c == '(' || c == '{' || c == '[')
                s.push(c);
            else
            {
                if (s.empty())
                    return false;
                if ((c == ')' && s.top() == '(') ||
                    (c == '}' && s.top() == '{') ||
                    (c == ']' && s.top() == '['))
                    s.pop();
                else
                    return false;
            }
        }
        return s.empty();
    }

    // 8. Sort Stack
    static void sortedInsert(stack<int> &s, int x)
    {
        if (s.empty() || x > s.top())
        {
            s.push(x);
            return;
        }
        int temp = s.top();
        s.pop();
        sortedInsert(s, x);
        s.push(temp);
    }
    static void sortStack(stack<int> &s)
    {
        if (s.empty())
            return;
        int x = s.top();
        s.pop();
        sortStack(s);
        sortedInsert(s, x);
    }

    // 9. Largest Rectangular Area in Histogram
    static int largestRectangle(vector<int> h)
    {
        stack<int> s;
        int maxA = 0, n = h.size(), i = 0;
        while (i < n)
        {
            if (s.empty() || h[s.top()] <= h[i])
                s.push(i++);
            else
            {
                int tp = s.top();
                s.pop();
                int area = h[tp] * (s.empty() ? i : i - s.top() - 1);
                maxA = max(maxA, area);
            }
        }
        while (!s.empty())
        {
            int tp = s.top();
            s.pop();
            int area = h[tp] * (s.empty() ? i : i - s.top() - 1);
            maxA = max(maxA, area);
        }
        return maxA;
    }

    // 10. Reverse Stack using Recursion
    static void insertAtBottom(stack<int> &s, int x)
    {
        if (s.empty())
        {
            s.push(x);
            return;
        }
        int temp = s.top();
        s.pop();
        insertAtBottom(s, x);
        s.push(temp);
    }
    static void reverseStack(stack<int> &s)
    {
        if (s.empty())
            return;
        int x = s.top();
        s.pop();
        reverseStack(s);
        insertAtBottom(s, x);
    }
};