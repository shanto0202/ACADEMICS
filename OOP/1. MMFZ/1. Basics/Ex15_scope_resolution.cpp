#include <iostream>
using namespace std;
int count = 0; // global variable
class X
{
public:
    static int count; // static member variable
};

int X::count = 10; // definition of static member

int main()
{

    int count = 0; // local variable

    // access global variable using scope resolution operator
    ::count = 1;
    count = 2;

    cout << "Global: " << ::count << endl;
    cout << "Local: " << count << endl;

    // access static class member
    cout << "Class count: " << X::count << endl;

    return 0;
}

/*
Key Notes:
1. Scope Resolution Operator (::) specifies the scope of a variable or function.
2. ::variable → accesses global variable when a local variable has same name.
3. ClassName::member → accesses static member of a class.
4. Helps avoid naming conflicts between global, local, and class variables.
*/