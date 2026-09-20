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

    // Unary operator overloading (++a)
    Coord operator++()
    {
        x++;
        y++;
        return *this; // return updated object
    }

    // Binary operator overloading (a += b)
    void operator+=(const Coord &ob)
    {
        x += ob.x;
        y += ob.y;
    }

    void show() const
    {
        cout << "(" << x << "," << y << ")" << endl;
    }
};

int main()
{
    Coord a(10, 20), b(2, 3);

    a += b; // left object (a) passed implicitly
    a.show();

    ++a; // unary operator
    a.show();

    // a++; // unary operator
    // a.show();

    b = ++a; // return object assigned to b
    b.show();
    return 0;
}

/*
Output
(12,23)
(13,24)
(14,25)


Key Notes:

1. In member operator functions, the left operand object is passed implicitly.

2. The implicit object is accessed through the "this" pointer.

3. Unary operators (like ++a) operate on one object.

4. Binary operators (like a += b) pass the right operand as argument.

5. Returning *this from operator++ allows expressions like:
      b = ++a;

6. If operator++ returns void, expressions like
      b = ++a
   will cause an error.
*/