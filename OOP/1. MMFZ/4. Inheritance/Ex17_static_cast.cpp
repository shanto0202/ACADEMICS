#include <iostream>
using namespace std;

class Base
{
public:
    virtual void print()
    {
        cout << "Base" << endl;
    }
};

class Derived : public Base
{
public:
    void print()
    {
        cout << "Derived" << endl;
    }
};

class MyClass
{
};

int main()
{
    float length = 4.26;
    int num = static_cast<int>(length); // explicit numeric cast
    float wide = num;
    char c = 'A';

    cout << "num: " << num << endl;
    cout << "length: " << length << endl;
    cout << "wide: " << wide << endl;

    Derived *d = new Derived;
    d->print(); // Derived

    Base *b = static_cast<Base *>(d); // upcast
    b->print();                       // Derived

    b = new Base();
    b->print(); // Base

    Base *base = new Base();
    Derived *derived = static_cast<Derived *>(base); // unsafe downcast
    derived->print();                                // Base

    derived = new Derived();
    derived->print();
    
    // float y = 9.1;
    // int x = static_cast<int>(y);
    // cout << x << endl;
    // int h = (int)y;
    return 0;
}

/*
Key Notes:

1. static_cast performs compile-time casting.

2. Safe for ordinary numeric conversion and upcasting.

3. Downcasting with static_cast is allowed syntactically but can be unsafe.

4. No runtime checking is done.
*/