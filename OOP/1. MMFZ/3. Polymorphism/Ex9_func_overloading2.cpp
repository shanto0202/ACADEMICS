#include <iostream>
using namespace std;

/* -------- Case 1: Call by Value vs Call by Reference -------- */

int f(int a, int b)
{ // call by value
    return a + b;
}

int f(int a, int &b)
{ // call by reference
    return a - b;
}

/* -------- Case 2: Default Argument Ambiguity -------- */

int g(int a)
{
    return a * a;
}

int g(int a, int b = 0)
{
    return a * b;
}

int main()
{

    int x = 1, y = 2;

    //cout << f(x, y) << endl; // ambiguous: value or reference?

    cout << g(10, 2) << endl; // calls g(int,int)
    //cout << g(10) << endl;    // ambiguous: g(int) or g(int,int=0)

    return 0;
}

/*
Key Notes:

1. Function overloading can become ambiguous when multiple functions
   match a call equally well.

2. Call by value and call by reference with same parameter types
   may create ambiguity.

3. Default arguments can also create ambiguity if another overloaded
   function already matches the call.

4. Compiler error: "call of overloaded function is ambiguous".

5. Java does not have these ambiguities because it does not support
   default arguments and handles references differently.
*/