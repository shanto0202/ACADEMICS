#include <iostream>
using namespace std;

/* -------- Overloaded Functions -------- */

void space(int count)
{
    for (; count; count--)
        cout << "_";
}

void space(int count, char ch)
{
    for (; count; count--)
        cout << ch;
}

int main()
{
    // function pointer declarations
    void (*fp1)(int);
    void (*fp2)(int, char);
    //space(10,'p');

    // assigning addresses of overloaded functions
    fp1 = space;
    fp2 = space;

    // calling through function pointers
    fp1(10);
    cout << endl;

    fp2(10, 'x');
    cout << endl;

    return 0;
}

/*
Output
__________
xxxxxxxxxx


Key Notes:

1. Function address can be obtained using the function name
   without parentheses.
      Example: p = func;

2. With overloaded functions, the compiler needs help to
   determine which version to use.

3. Function pointers specify the parameter types,
   which resolves the correct overloaded function.

4. Java does NOT allow address-level access to functions.
*/