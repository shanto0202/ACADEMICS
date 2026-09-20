#include <iostream>
using namespace std;

// First class
class MyClass
{
    int a, b;

public:
    // function to set values
    void setValue(int n, int m)
    {
        a = n;
        b = m;
    }
    // function to display values
    void show()
    {
        cout << a << ", " << b << endl;
    }
};
 
// Second class
class YourClass
{
    int a, b;

public:
    void setValue(int n, int m)
    {
        a = n;
        b = m;
    }
    void show()
    {
        cout << a << ", " << b << endl;
    }
};

int main()
{
    MyClass ob1, ob2;
    YourClass ob3;
    ob1.setValue(10, 20);
    ob2 = ob1; // object assignment (same class) ✔
    // ob3 = ob1;   // ❌ error: different class types
    ob1.show();
    ob2.show();
    return 0;
}