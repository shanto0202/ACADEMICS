#include <iostream>
using namespace std;

class StaticDemo
{
    static const int b = 5;
    int n = 4, m = 5; // non-static members

public:
    static int a; // static variable (shared by all objects)
    // static method
    static void increment()
    {
        a++; // static methods can access only static members
        // n++;
    }

    // non-static method
    int getProduct()
    {
        return n * m;
    }

    // static display method
    static void display()
    {
        cout << "A: " << a << " B: " << b << endl;
    }
};

// definition of static variable
int StaticDemo::a = 0;

int main()
{
    StaticDemo sd;
    sd.display();        // display static values
    sd.increment();      // increment static variable
    StaticDemo::display; // call using class name
    cout << StaticDemo::a << endl;
    cout << sd.getProduct() << endl;
    return 0;
}

/*
Key Notes:
1. static variable → only one copy shared by all objects of the class.
2. Static members can be accessed using ClassName::member.
3. Static methods can access only static variables and static methods.
4. Static methods cannot use non-static members directly.
5. Static variables must be defined outside the class.
*/