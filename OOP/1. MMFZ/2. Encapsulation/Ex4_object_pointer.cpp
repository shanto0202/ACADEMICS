#include <iostream>
using namespace std;

class MyClass
{
    int a;

public:
    MyClass()
    {
        a = 10;
    }
    MyClass(int x)
    {
        a = x;
    }
    int getA()
    {
        return a;
    }
};

int main()
{
    // There is no pointer operator in Java.
    MyClass ob(120);
    MyClass *p;
    p = &ob;
    cout << "Object Value: " << ob.getA() << endl;
    cout << "Value using pointer: " << p->getA() << endl;
    return 0;
}