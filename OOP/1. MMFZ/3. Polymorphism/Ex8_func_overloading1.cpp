#include <iostream>
using namespace std;

/* -------- Case 1: Automatic Type Conversion -------- */

float f(float i)
{
    return i / 2.0;
}

double f(double i)
{
    return i / 3.0;
}

/* -------- Case 2: Similar Argument Types -------- */

void g(unsigned char c)
{
    cout << c << endl;
}

void g(char c)
{
    cout << c << endl;
}

int main()
{

    float x = 10.09;
    double y = 10.09;

    cout << f(x) << endl; // calls float version
    cout << f(y) << endl; // calls double version

    // cout << f(10) << endl; // ambiguous: int → float or double
    cout << f((double)10) << endl;

    g('c'); // calls char version

    // g(86);  // ambiguous: int → char or unsigned char

    return 0;
}

/*
Key Notes:

1. Function overloading allows multiple functions with the same name
   but different parameter types.

2. Ambiguity occurs when the compiler cannot decide which function to call.

3. Automatic type conversion can cause ambiguity.
   Example: int can convert to float or double.

4. Similar argument types may also cause ambiguity.
   Example: int can convert to char or unsigned char.

5. Explicit type casting can resolve ambiguity.
   Example:
       f((float)10);
       g((char)86);
*/