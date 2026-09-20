#include <iostream>
#include <iomanip>
using namespace std;

int main()
{

    cout << hex << 100 << endl; // hexadecimal output
    cout << oct << 10 << endl;  // octal output

    cout << setfill('*') << setw(10); // width and fill manipulator
    cout << dec << 100 << " hi" << endl;

    return 0;
}

/*
Key Notes:

1. Manipulators modify stream formatting.

2. <iomanip> required for manipulators with parameters.

3. Examples:
      hex → hexadecimal output
      oct → octal output
      setw(n) → set field width
      setfill(ch) → fill character.
*/