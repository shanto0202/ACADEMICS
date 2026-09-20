#include <iostream>
using namespace std;

// unnamed namespace (visible only within this file)
namespace
{
    void displayMsg()
    {
        cout << "unnamed namespace." << endl;
    }
    int add(int a, int b)
    {
        return a + b;
    }
}

int main()
{
    displayMsg();

    int result = add(5, 3);
    cout << "Result: " << result << endl;

    return 0;
}

/*
Key Notes:
1. Namespace → declarative region used to organize identifiers.
2. std → standard namespace containing library functions (cout, cin, etc.).
3. Unnamed namespace → accessible only within the same source file.
4. Used to avoid name conflicts and improve modularity.
5. using namespace std; allows direct use of std members without std::.
*/