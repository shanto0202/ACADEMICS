#include <iostream>
using namespace std;

// First declaration of namespace
namespace Demo
{
    int a;
}

int x;

// Second declaration of the same namespace
namespace Demo
{
    int b;
}

int main()
{

    using namespace Demo;

    a = b = x = 100;

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "x: " << x << endl;

    return 0;
}

/*
Key Notes:
1. A namespace can be declared multiple times in the same file or different files.
2. All declarations with the same namespace name are merged by the compiler.
3. using namespace Demo; allows direct access to members inside Demo.
4. Namespaces help organize large programs and avoid naming conflicts.
*/