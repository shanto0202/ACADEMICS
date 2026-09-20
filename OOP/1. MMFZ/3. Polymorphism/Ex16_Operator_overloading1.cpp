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

    /* Binary operator: Coord + Coord */
    Coord operator+(Coord ob)
    {
        Coord temp;
        temp.x = x + ob.x;
        temp.y = y + ob.y;
        return temp;
    }

    /* Binary operator: Coord + int */
    Coord operator+(int i)
    {
        Coord temp;
        temp.x = x + i;
        temp.y = y + i;
        return temp;
    }

    /* Postfix increment */
    Coord operator++(int notused)
    {
        Coord temp = *this;
        x++;
        y++;
        return temp;
    }

    /* Prefix increment */
    Coord operator++()
    {
        ++x;
        ++y;
        return *this;
    }

    /* Assignment operator */
    Coord operator=(Coord ob)
    {
        x = ob.x;
        y = ob.y;
        return *this;
    }

    /* Friend operators */
    friend bool operator==(int v, Coord ob) // left object implicitly paased, right one argument
    {
        return (v == ob.x && v == ob.y);
    }

    friend Coord operator+(int v, Coord ob)
    {
        Coord temp;
        temp.x = v + ob.x;
        temp.y = v + ob.y;
        return temp;
    }

    void show() const
    {
        cout << "(" << x << "," << y << ")" << endl;
    }
};

int main()
{

    Coord a(10, 20), b(2, 3), c;

    c = a + b;
    c.show();

    c = a + 5;
    c.show();

    c = 100 + b;
    c.show();

    ++a;
    a.show();

    b++;
    b.show();

    return 0;
}

/*
Example Output
(12,23)
(15,25)
(102,103)
(11,21)
(3,4)


Key Notes:

1. Operator overloading allows operators to work with user-defined objects.
2. Unary operators (++a, a++) work on one object.
3. Binary operators (a + b) work on two operands.
4. In member operator functions:
      left operand → implicit object (*this)
      right operand → function parameter.
5. Friend functions are needed when the left operand is not an object
   (example: 100 + obj).
6. Prefix (++a) returns updated object, postfix (a++) returns old value.
*/