#include <iostream>
using namespace std;

class ObArg
{
    int a;

public:
    ObArg(int n)
    {
        a = n;
        cout << "Constructing..." << endl;
    }
    ~ObArg()
    {
        cout << "Destructing..." << endl;
    }
    void setA(int n)
    {
        a = n;
    }
    int getA()
    {
        return a;
    }
};

void sqrOb(ObArg ob) // if &ob, then After sqrOb: 100
{
    //cout << ob.getA() << endl;
    ob.setA(ob.getA() * ob.getA()); // shallow copy
    cout << "Inside sqrOb: " << ob.getA() << endl;
}

int main()
{
    ObArg ob1(10);
    cout << "Before sqrOb: " << ob1.getA() << endl;
    sqrOb(ob1);
    cout << "After sqrOb: " << ob1.getA() << endl;
    return 0;
}