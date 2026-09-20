#include <iostream>
using namespace std;

class Coord
{
    int x, y;

public:
    Coord(int x = 0, int y = 0) : x(x), y(y)
    {
    }

    void show() const
    {
        cout << "(" << x << "," << y << ")" << endl;
    }

    // friend operator declarations
    friend Coord operator+(const Coord &c1, const Coord &c2);
    friend Coord operator+(const Coord &c, int n);
    friend Coord operator+(int n, const Coord &c);

    friend Coord operator++(Coord &c);      // prefix
    friend Coord operator++(Coord &c, int); // postfix
};

// Coord + Coord
Coord operator+(const Coord &c1, const Coord &c2)
{
    return Coord(c1.x + c2.x, c1.y + c2.y);
}

// Coord + int
Coord operator+(const Coord &c, int n)
{
    return Coord(c.x + n, c.y + n);
}

// int + Coord
Coord operator+(int n, const Coord &c)
{
    return Coord(n + c.x, n + c.y);
}

// prefix ++
Coord operator++(Coord &c)
{
    ++c.x;
    ++c.y;
    return c;
}

// postfix ++
Coord operator++(Coord &c, int)
{
    Coord temp = c;
    ++c.x;
    ++c.y;
    return temp;
}

int main()
{

    Coord c1(1, 2), c2(3, 4);

    Coord c3 = c1 + c2;
    c3.show();

    Coord c4 = c1 + 5;
    c4.show();

    Coord c5 = 5 + c1;
    c5.show();

    ++c1;
    c1.show();

    c1++;
    c1.show();

    return 0;
}

/*
Key Notes:

1. Friend functions allow operator overloading when the left operand is not the class object.
   Example: 5 + obj

2. Friend functions do not have a "this" pointer.

3. All operands are passed explicitly as parameters.

4. Using friend allows both:
      obj + 5
      5 + obj

5. Prefix ++ returns modified object.
6. Postfix ++ returns old copy of object.
*/