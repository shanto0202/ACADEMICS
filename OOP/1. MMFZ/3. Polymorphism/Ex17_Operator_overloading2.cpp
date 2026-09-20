#include <iostream>
using namespace std;

class Coord
{
    int x, y;

public:
    Coord(int a = 0, int b = 0)
    {
        x = a;
        y = b;
    }

    void getxy(int &i, int &j)
    {
        i = x;
        j = y;
    }
    //---------------- unary operators ----------------/

    // prefix ++ → increment first, then return updated object
    Coord operator++()
    {
        x++;
        y++;
        return *this;
    }

    // postfix ++ → return old object, then increment
    Coord operator++(int notused)
    {
        Coord temp = *this;
        x++;
        y++;
        return temp;
    }

    //---------------- binary operators ----------------/

    // multiply two Coord objects
    Coord operator*(Coord ob)
    {
        Coord temp;
        temp.x = x * ob.x;
        temp.y = y * ob.y;
        return temp;
    }

    // add two Coord objects
    Coord operator+(Coord ob)
    {
        Coord temp;
        temp.x = x + ob.x;
        temp.y = y + ob.y;
        return temp;
    }

    // add integer with Coord object (int on left side)
    friend Coord operator+(int x, Coord ob)
    {
        Coord temp;
        temp.x = x + ob.x;
        temp.y = x + ob.y;
        return temp;
    }

    // add integer with Coord object (object on left side)
    Coord operator+(int p)
    {
        Coord temp;
        temp.x = x + p;
        temp.y = y + p;
        return temp;
    }

    // compare if both x and y equal the integer value
    friend bool operator==(int x, Coord ob)
    {
        return (x == ob.x && x == ob.y);
    }

    // overloaded assignment operator
    Coord operator=(Coord ob)
    {
        x = ob.x + 100; // just for testing
        y = ob.y + 100; // just for testing
        return *this;
    }
};

int main()
{

    Coord a(10, 20), b(4, 4), c;
    int x, y;

    c = a++; // c= 110 120 a=11 21
    c.getxy(x, y);
    cout << x << " " << y << endl;
    a.getxy(x, y);
    cout << x << " " << y << endl;
    c = ++a; // c=112 122 a= 12 22
    c.getxy(x, y);
    cout << x << " " << y << endl;
    a.getxy(x, y);
    cout << x << " " << y << endl;
    (a * b).getxy(x, y); // 48 88
    cout << x << " " << y << endl;
    if (4 == b)
        cout << "Equal" << endl;
    else
        cout << "Not equal" << endl;
    (20 + a).getxy(x, y);
    cout << x << " " << y << endl;
    (a + b + c + 100).getxy(x, y); // 128 248  //left associative +,-,*,/ right assosiative >,<,==
    cout << x << " " << y << endl;
    c = a++; //
    c.getxy(x, y);
    cout << x << " " << y << endl;

    return 0;
}

/*
Key Notes:

1. Operator overloading allows operators to work with objects.

2. Prefix ++a → increment first, return updated object.

3. Postfix a++ → return old value, then increment.

4. Member operator: left operand passed implicitly (*this).

5. Friend operator used when left operand is not an object
   (example: 20 + a , 4 == b).
*/