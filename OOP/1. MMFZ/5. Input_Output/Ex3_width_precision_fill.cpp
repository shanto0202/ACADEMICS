#include <iostream>
#include <cmath>
using namespace std;

int main()
{

    cout << "Hello " << endl;
    cout << 123.456789 << endl;

    cout.width(10);
    cout << "Hello" << endl; // field width

    cout.width(10);
    cout.fill('*');
    cout << "Hello" << endl; // fill unused spaces with * //*****Hello

    cout.precision(8);
    cout << 123.456376 << endl; // set precision

    cout.width(12);
    cout.fill('%');
    cout.setf(ios::left); // left aligned output

    cout << 123.456786 << endl;

    cout.fill('_');
    cout.setf(ios::right); // right aligned
    cout.precision(4);
    cout << 123.456789 << endl;

    for (double x = 2.0; x <= 5; x++)
    {

        cout.width(7);
        cout << x;

        cout.width(12);
        cout << sqrt(x);

        cout.width(7);
        cout << x * x << endl;
    }

    return 0;
}

/*
Key Notes:

1. width(n) → sets minimum field width.

2. fill(ch) → sets character used for padding.

3. precision(p) → controls digits of floating output.

4. setf(ios::left / ios::right) → alignment control.
*/