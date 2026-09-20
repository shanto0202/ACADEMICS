#include <iostream>
using namespace std;

// function template
template <class X>
void swapargs(X &a, X &b)
{
    X temp; // temporary variable of same type
    temp = a;
    a = b;
    b = temp;
}

int main()
{
    int i = 10, j = 20;
    double x = 10.1, y = 23.3;
    char a = 'x', b = 'z';

    cout << "Original i, j: " << i << ' ' << j << '\n';
    cout << "Original x, y: " << x << ' ' << y << '\n';
    cout << "Original a, b: " << a << ' ' << b << '\n';

    swapargs(i, j); // swaps int values
    swapargs(x, y); // swaps double values
    swapargs(a, b); // swaps char values

    cout << "Swapped i, j: " << i << ' ' << j << '\n';
    cout << "Swapped x, y: " << x << ' ' << y << '\n';
    cout << "Swapped a, b: " << a << ' ' << b << '\n';

    return 0;
}

/*
Key Notes:

1. Template Function → one function can work with different data types.
2. Syntax:
   template <class X>
3. Compiler creates the needed version automatically.
4. Here the same function works for int, double, and char.
5. Reference parameters (&) are used so original values are swapped.
*/