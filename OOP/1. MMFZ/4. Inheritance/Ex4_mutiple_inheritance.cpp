#include <iostream>
using namespace std;

class B1
{
    int x;

public:
    B1(int i)
    {
        x = i;
        cout << "Constructing B1\n";
    }
    ~B1()
    {
        cout << "Destructing B1\n";
    }
    int getx()
    {
        return x;
    }
};

class B2
{
    int y;

public:
    B2(int j)
    {
        y = j;
        cout << "Constructing B2\n";
    }
    ~B2()
    {
        cout << "Destructing B2\n";
    }
    int gety()
    {
        return y;
    }
};

class D1 : public B1
{
public:
    D1(int j) : B1(j)
    {
        cout << "Constructing D1\n";
    }
    ~D1()
    {
        cout << "Destructing D1\n";
    }
};

class B3
{
    int z;

public:
    B3(int k)
    {
        z = k;
        cout << "Constructing B3\n";
    }
    ~B3()
    {
        cout << "Destructing B3\n";
    }
    int getz()
    {
        return z;
    }
};

class D2 : public D1, public B2, public B3
{
    // multiple inheritance
public:
    D2(int i, int j, int k) : D1(i), B2(j), B3(k) // B1 D1 B2 B3 D2
    {
        cout << "Constructing D2\n";
    }
    ~D2()
    {
        cout << "Destructing D2\n";
    }
    void show()
    {
        cout << getx() << " " << gety() << " ";
        cout << getz() << '\n';
    }
};

int main()
{
    D2 ob(10, 20, 30);
    ob.show();
    return 0;
}

/*
Key Notes:

1. D2 inherits from D1, B2, and B3.

2. Constructors execute left to right.

3. Destructors execute in reverse order.

4. Java does not support multiple base inheritance.
*/