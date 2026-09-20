#include <bits/stdc++.h>
using namespace std;

bool isBalanced(string s)
{
    stack<int> st;

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(')
        {
            st.push(i);
        }
        else if (s[i] == ')')
        {
            if (st.empty())
                return false;

            st.pop();
        }
    }

    return st.empty();
}

int firstOffendingPosition(string s)
{
    stack<int> st;

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(')
        {
            st.push(i);
        }
        else if (s[i] == ')')
        {
            if (st.empty())
                return i; // excess right parenthesis

            st.pop();
        }
    }

    if (!st.empty())
    {
        int firstExcessLeft = st.top();

        while (!st.empty())
        {
            firstExcessLeft = st.top();
            st.pop();
        }

        return firstExcessLeft;
    }

    return -1; // properly balanced
}

int main()
{
    string s;
    cin >> s;

    if (isBalanced(s))
        cout << "Balanced" << endl;
    else
        cout << "Not Balanced" << endl;

    cout << "First offending position = " << firstOffendingPosition(s) << endl;

    return 0;
}

/*
Key Notes:

1. Use a stack to store indices of '('.

2. When '(' is found:
   Push its index into stack.

3. When ')' is found:
   - If stack is empty, this ')' has no matching '('.
     So this is the first offending parenthesis.
   - Otherwise pop one '(' from stack.

4. After scanning the string:
   - If stack is empty, string is balanced.
   - If stack is not empty, there are excess '('.

5. For excess '(':
   The first excess left parenthesis is the bottom-most index in stack.

6. Return values:
   - Return index of first offending parenthesis if invalid.
   - Return -1 if string is valid.

7. Time Complexity:
   O(n)

8. Space Complexity:
   O(n)
*/