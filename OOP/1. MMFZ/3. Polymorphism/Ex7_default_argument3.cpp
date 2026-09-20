#include <iostream>
using namespace std;

class myclass
{
    int x;

public:
    myclass(int n = 0)
    {
        x = n;
    } // constructor with default argument
    int getx()
    {
        return x;
    }
};

int main()
{
    myclass o1(10); // value given
    myclass o2;     // default value used

    cout << o1.getx() << endl;
    cout << o2.getx() << endl;
}

/*
Key Notes:
1. Constructors can also have default arguments.
2. Object can be created with or without parameter.
3. Java does NOT support default arguments.
*/