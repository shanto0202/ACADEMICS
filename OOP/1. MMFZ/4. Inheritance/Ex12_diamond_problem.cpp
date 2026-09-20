#include <iostream>
using namespace std;

class B
{
public:
    int i;
};

class D1 : virtual public B
{ // virtual inheritance
public:
    int j;
};

class D2 : virtual public B
{ // virtual inheritance
public:
    int k;
};

class D3 : public D1, public D2
{
public:
    int product()
    {
        return i * j;
    }
};

int main()
{
    D1 ob1;
    D3 ob3;
    ob1.i = 100;
    ob3.i = 10;
    ob3.j = 3;
    cout << ob1.i << endl;
    cout << ob3.i << endl;
    cout << ob3.product() << endl;
    return 0;
}

/*
Key Notes:

1. Virtual inheritance removes duplicate B copies in D3.

2. Prevents ambiguity of inherited base members.

3. Classic solution to diamond problem in C++.
*/