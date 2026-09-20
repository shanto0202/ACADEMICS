#include <iostream>
using namespace std;

int main()
{

    ios::fmtflags f = cout.flags(); // store current format flags

    cout << 123.45 << " Hello " << -10 << " " << 100.0 << " " << 100 << endl;

    cout.unsetf(ios::dec);                              // remove decimal formatting
    cout.setf(ios::hex | ios::showbase | ios::showpos); // enable hex, base and sign

    cout << 123.45 << " Hello " << -10 << " " << 100.0 << " " << 100 << endl;

    ios::fmtflags f2 = ios::scientific | ios::showpoint | ios::uppercase;
    cout.setf(f2); // keeps previous one allso, enable scientific notation and uppercase

    cout << 123.45 << " Hello " << -10 << " " << 100.0 << " " << 100 << endl;

    if (f & ios::dec)
        cout << "Dec is set" << endl; // check if decimal flag active

    cout.flags(f); // removes previous ones, restore original flags

    cout << 123.45 << " Hello " << -10 << " " << 100.0 << " " << 100 << endl;

    return 0;
}

/*
Key Notes:

1. fmtflags control formatting of stream output.

2. setf() → enable format flags.
   unsetf() → disable format flags.

3. Examples:
      ios::hex → hexadecimal output
      ios::showbase → show base prefix (0x)
      ios::showpos → show + sign for positive numbers.

4. flags() can store and restore previous formatting state.
*/