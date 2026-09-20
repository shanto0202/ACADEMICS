#include <bits/stdc++.h>
#define ll long long
using namespace std;
bool isPalindrome(queue<ll> &q)
{
    stack<ll> st;
    int n = q.size();
    for (int i = 0; i < n; i++)
    {
        st.push(q.front());
        q.push(q.front());
        q.pop();
    }
    for (int i = 0; i < n; i++)
    {
        if (q.front() != st.top())
            return false;
        st.pop();
        q.push(q.front());
        q.pop();
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    queue<ll> q;
    for (char c : s)
    {
        q.push(c - '0');
    }
    if (isPalindrome(q))
    {
        cout << "Palindrome\n";
    }
    else
    {
        cout << "Not Palindrome\n";
    }
    return 0;
}