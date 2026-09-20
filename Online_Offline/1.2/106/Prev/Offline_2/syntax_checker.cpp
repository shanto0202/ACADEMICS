#include <bits/stdc++.h>
#define tata "\n"
#define ll long long
#define pb push_back
#define loop(i, j, n) for (ll i = j; i < n; i++)
using namespace std;

/**
 * Helper function to check if an opening bracket matches a closing bracket
 * @param opening: The opening bracket character
 * @param closing: The closing bracket character
 * @return true if they form a matching pair, false otherwise
 */
bool isMatchingPair(char opening, char closing)
{
    if (opening == '(' && closing == ')')
        return true;
    if (opening == '[' && closing == ']')
        return true;
    if (opening == '{' && closing == '}')
        return true;
    // TODO: Implement this helper function
    // Check if opening and closing brackets match
    // Valid pairs: (), [], {}
    return false; // Replace this with your implementation
}

/**
 * Checks if brackets in an arithmetic expression are properly matched
 * @param expression: A string containing an arithmetic expression
 * @return true if all brackets are properly matched and balanced, false otherwise
 */
bool isValidExpression(const string &expression)
{
    // TODO: Implement the syntax checker using std::stack
    stack<char> s;
    for (char c : expression)
    {
        if (c == '(' || c == '[' || c == '{')
        {
            s.push(c);
        }
        else if (c == ')' || c == ']' || c == '}')
        {
            if (s.empty())
            {
                return false;
            }
            char t = s.top();
            s.pop();
            if (!isMatchingPair(t, c))
            {
                return false;
            }
        }
    }
    return s.empty(); // Replace this with your implementation
}