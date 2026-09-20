#include <iostream>
using namespace std;

// template with two type parameters
template <class type1, class type2>
void myfunc(type1 x, type2 y)
{
    cout << x << ' ' << y << '\n';
}

int main()
{
    myfunc(10, "I like C++"); // int and string literal
    myfunc(98.6, 19L);        // double and long

    return 0;
}

/*
Key Notes:

1. A template can take more than one type parameter.
2. Syntax:
   template <class type1, class type2>
3. Useful when function arguments are of different types.
4. Compiler deduces the types from the passed arguments.
*/