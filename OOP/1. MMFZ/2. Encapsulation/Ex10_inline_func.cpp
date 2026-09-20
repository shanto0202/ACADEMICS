#include <iostream>
using namespace std;
/*
 The 'inline' keyword suggests the compiler replace the function
 call with the function body to reduce function call overhead.
*/
// Java does not support inline function
inline int even(int x)
{
    return (x % 2 == 0);
}

bool check(int x)
{
    return (x % 2 == 0);
}

int main()
{
    if (check(3))
    {
        cout << "Odd" << endl;
    }
    if (even(10))
    {
        cout << "Even" << endl;
    }
    return 0;
}