#include <iostream>
using namespace std;

// Function with default arguments
void f(int a = 0, int b = 0)
{
    cout << a << " " << b << endl;
}

int main()
{
    f();       // uses both default values
    f(10);     // uses default value for b
    f(10, 99); // no default used
}

/*
Key Notes:

1. Default arguments allow a function to be called with fewer parameters.

2. Default values can be specified either
   - in the function prototype, or
   - in the function definition
   but NOT in both.

3. Default parameters must be placed on the right side of parameters
   that do not have default values.

   Example:
   void func(int a, int b = 5);   // correct
   void func(int a = 5, int b);   // wrong

4. If a value is passed during function call, it overrides the default value.
*/