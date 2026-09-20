#include <iostream>
using namespace std;

// first namespace
namespace firstNS
{
    int x;
    class MyClass
    {
        int i;

    public:
        MyClass(int n)
        {
            i = n;
        }
        void setI(int n)
        {
            i = n;
        }
        int getI()
        {
            return i;
        }
    };

    const char *str = "Hello from firstNS!";
    int counter = 0;
}

// second namespace
namespace secondNS
{
    int x, y;
}

int main()
{

    firstNS::MyClass ob(10);

    ob.setI(99);
    cout << "I: " << ob.getI() << endl;

    using firstNS::str;
    cout << str << endl;

    using namespace firstNS;
    for (counter = 10; counter > 0; counter--)
        cout << counter << " ";
    cout << endl;

firstNS:
    x = 5;

    secondNS::x = 10;
    secondNS::y = 20;

    cout << "First NS of X: " << firstNS::x << endl;

    cout << "X: " << secondNS::x << endl;
    cout << "Y: " << secondNS::y << endl;

    return 0;
}

/*
Key Notes:
1. Custom namespaces can be created using: namespace name { }.
2. Members are accessed using scope resolution operator (::).
3. using namespace name → allows direct access to all members.
4. using name::member → imports only a specific member.
5. Namespaces help avoid name conflicts and organize large programs.
*/