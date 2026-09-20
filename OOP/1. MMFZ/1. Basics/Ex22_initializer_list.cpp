#include <iostream>
using namespace std;
class Point
{
    int x, y;

public:
    // Constructor 1: normal assignment
    Point(int a, int b)
    {
        x = a;
        y = b;
        cout << "Constructor 1 (normal assignment)" << endl;
    }

    // Constructor 2: initializer list
    Point(int a) : x(a), y(a)
    {
        cout << "Constructor 2 (initializer list)" << endl;
    }

    // Constructor 3: initializer list with printing
    Point() : x(0), y(0)
    {
        cout << "Constructor 3 (default initializer list)" << endl;
        cout << "x: " << x << endl;
        cout << "y: " << y << endl;
    }

    void display()
    {
        cout << "x: " << x << endl;
        cout << "y: " << y << endl;
    }
};

int main()
{

    Point p1(10, 20); // uses constructor 1
    p1.display();
    cout << endl;
    Point p2(5); // uses constructor 2
    p2.display();
    cout << endl;
    Point p3; // uses constructor 3
    return 0;
}

/*
Key Notes:
1. Multiple constructors in a class are called Constructor Overloading.
2. Constructor can initialize members using:
   - assignment inside constructor body
   - initializer list (: x(a), y(b)).
3. Initializer list is more efficient because members are initialized directly.
4. Default constructor → constructor with no parameters.
5. Constructor used depends on the arguments during object creation.
*/