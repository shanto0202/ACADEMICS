#include <iostream>
using namespace std;

// first template version
template <class X>
void f(X a)
{
    cout << "Inside f(X a)\n";
}

// second template version
template <class X, class Y>
void f(X a, Y b)
{
    cout << "Inside f(X a, Y b)\n";
}

int main()
{
    f(10);     // calls one-parameter version
    f(10, 20); // calls two-parameter version

    return 0;
}

/*
Key Notes:

1. Function templates can be overloaded.
2. Compiler chooses the correct version from argument count/type.
3. First template takes one argument.
4. Second template takes two arguments.
*/