#include <iostream>
using namespace std;
const int TABWIDTH = 8;
// X is generic, tab is a normal int parameter
template <class X>
void tabOut(X data, int tab)
{
    for (; tab; tab--) // repeat tab times
    {
        for (int i = 0; i < TABWIDTH; i++)
        {
            cout << ' '; // print spaces
        }
    }
    cout << data << "\n";
}

int main()
{
    tabOut("This is a test", 0);
    tabOut(100, 1);
    tabOut('X', 2);
    tabOut(10 / 3, 3);

    return 0;
}

/*
Key Notes:

1. Template functions may also have ordinary parameters.
2. Here data type is generic, but tab is fixed as int.
3. Function prints output after giving tab spacing.
*/