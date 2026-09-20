#include <iostream>
#include <cstdlib>
using namespace std;

class Myclass
{
    int a;

public:
    // explicit constructor: prevents implicit conversion from int
    explicit Myclass(int x)
    {
        a = x;
    }

    // constructor from string
    Myclass(char *str)
    {
        a = atoi(str); // convert string to integer
    }

    int getA()
    {
        return a;
    }
};

int main()
{

    Myclass ob1(10);

    //Myclass ob2 = 20;  // ERROR: implicit conversion not allowed (because of explicit)

    Myclass ob3("40"); // string constructor called

    Myclass ob4 = "60"; // implicit conversion using char* constructor

    cout << "ob1: " << ob1.getA() << endl;
    //cout << "ob2: " << ob2.getA() << endl;
    cout << "ob3: " << ob3.getA() << endl;
    cout << "ob4: " << ob4.getA() << endl;

    return 0;
}

/*
Key Notes:

1. Type conversion from primitive type → class type can occur using constructors.

2. explicit keyword prevents implicit conversion.
   Example: Myclass ob2 = 20; → not allowed.

3. Constructors without explicit allow implicit conversion.

4. atoi() converts a string to an integer.

5. Example conversions:
      Myclass ob1(10);   → explicit call
      Myclass ob3("40"); → string constructor
      Myclass ob4 = "60"; → implicit conversion
*/