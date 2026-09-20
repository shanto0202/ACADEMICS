#include <iostream>
using namespace std;

class myclass
{
    int a;

public:
    myclass(); // constructor
    int geta()
    {
        return a;
    }
};

myclass::myclass()
{
    cout << "In constructor\n";
    a = 10;
}

int main()
{
    myclass ob;
    // cout << a;   // wrong
    cout << ob.geta(); // OK

    return 0;
}