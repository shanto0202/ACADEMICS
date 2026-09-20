#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define jora(p, n) pair<ll, ll> p(n)
#define sajai(x) sort(x.begin(), x.end())
#define arr(v, x, y) vector<vector<ll>> v(x, vector<int>(y))
#define loop(i, j, n) for (ll i = j; i < n; i++)
#define in(v) loop(i, 0, v.size()) cin >> v[i]
#define out(v) loop(i, 0, v.size()) cout << v[i] << " "
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define tata "\n"
using namespace std;

void reverseQueue(queue<ll> &q)
{
    stack<ll> st;
    while (!q.empty())
    {
        st.push(q.front());
        q.pop();
    }
    while (!st.empty())
    {
        q.push(st.top());
        st.pop();
    }
};
void reverseStack(stack<ll> &s)
{
    stack<ll> s2;
    while (!s.empty())
    {
        s2.push(s.top());
        s.pop();
    }
    s = s2;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    stack<ll> st;
    queue<ll> q;
    string s;
    cin >> s;
    for (auto &x : s)
    {
        q.push(x - '0');
        st.push(x - '0');
    }
    reverseQueue(q);
    reverseStack(st);
    while (!q.empty())
    {
        cout << q.front();
        q.pop();
    }
    cout << tata;
    while (!st.empty())
    {
        cout << st.top();
        st.pop();
    }
    return 0;
}