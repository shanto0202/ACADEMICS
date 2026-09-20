// Demonstrates inheritance (derived class inherits base class properties)

#include <iostream>
using namespace std;

// Base class (Superclass)
class base
{
    int x;

public:
    void setx(int n)
    {
        x = n;
    }

    void showx()
    {
        cout << x << '\n';
    }

    int getx()
    {
        return x;
    }
};

// Derived class (Subclass)
class derived : public base
{
    int y;

public:
    void sety(int n)
    {
        y = n;
    }

    void showy()
    {
        cout << y << '\n';
        cout << y + getx() << '\n'; // access base class data through method
    }
};

int main()
{
    derived ob;

    ob.setx(10); // inherited method from base
    ob.sety(20); // method of derived class

    ob.showx(); // prints 10
    ob.showy(); // prints 20 and 30

    return 0;
}

/*
Key Notes:
1. Inheritance → one class acquires properties of another class.
2. base = superclass, derived = subclass.
3. "public base" → public inheritance.
4. Derived class can use public methods of base class.
5. Promotes code reuse and hierarchical classification.
*/