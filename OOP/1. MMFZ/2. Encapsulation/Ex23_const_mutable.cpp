#include <iostream>
using namespace std;

class Demo
{
    mutable int a; // mutable member
    int b;

public:
    Demo()
    {
        a = 0;
        b = 0;
    }
    Demo(int a1, int b1)
    {
        a = a1;
        b = b1;
    }
    int getA() const
    {
        return a;
    }

    int getB() const
    {
        return b;
    }

    // const member function
    void setAB(int x, int y) const
    {
        a = x; // allowed because 'a' is mutable
        // b = y;     // not allowed in const function
    }
};

int main()
{
    const Demo d(5, 6);
    d.setAB(10, 20);
    cout << "A: " << d.getA() << endl;
    cout << "B: " << d.getB() << endl;
    return 0;
}

/*
Key Notes:
1. const member function → cannot modify non-mutable data members.
2. Syntax: returnType function() const.
3. mutable keyword → allows modification even inside const functions.
4. const object → can call only const member functions.
5. Non-member functions cannot be declared const.
*/