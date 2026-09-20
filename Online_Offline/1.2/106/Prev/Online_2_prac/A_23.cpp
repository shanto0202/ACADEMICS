#include <bits/stdc++.h>
#define ll long long
using namespace std;

class MyQueue
{
    stack<ll> in, out;
    void shift()
    { // move only when needed
        if (!out.empty())
            return;
        while (!in.empty())
        {
            out.push(in.top());
            in.pop();
        }
    }

public:
    void enqueue(ll x)
    {
        in.push(x);
    }

    ll dequeue()
    {
        shift();
        if (out.empty())
            return -1; // or throw
        ll x = out.top();
        out.pop();
        return x;
    }

    ll front()
    {
        shift();
        if (out.empty())
            return -1; // or throw
        return out.top();
    }

    bool empty()
    {
        return in.empty() && out.empty();
    }

    int size()
    {
        return (int)in.size() + (int)out.size();
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    MyQueue q;

    // simple test
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    cout << q.front() << "\n";   // 1
    cout << q.dequeue() << "\n"; // 1
    cout << q.dequeue() << "\n"; // 2

    q.enqueue(4);

    while (!q.empty())
    {
        cout << q.dequeue() << " "; // 3 4
    }
    cout << "\n";

    return 0;
}