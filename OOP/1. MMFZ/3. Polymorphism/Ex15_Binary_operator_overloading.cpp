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

    /* Binary operator that changes object (a += b) */
    Coord operator+=(Coord ob)
    {
        x += ob.x;
        y += ob.y;
        return *this; // return updated object
    }

    /* Binary operator that does NOT change object (a * b) */
    Coord operator*(Coord ob)
    {
        Coord temp;
        temp.x = x * ob.x;
        temp.y = y * ob.y;
        return temp;
    }

    /* Friend function required when object is NOT on left side (100 + ob) */
    friend Coord operator+(int n, Coord ob)
    {
        Coord temp;
        temp.x = n + ob.x;
        temp.y = n + ob.y;
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

    a += b; // object changed
    a.show();

    c = a * b; // object not changed
    c.show();

    c = 100 + b; // friend operator used
    c.show();

    return 0;
}

/*
Example Output
(12,23)
(24,69)
(102,103)


Key Notes:

1. Binary operators work with two operands.
2. If the object is on the left side (a + b), member operator can be used.
3. If the object is NOT on the left side (100 + ob), a friend operator is required.
4. Some binary operators modify objects (+=), others return new objects (*, +).
5. Left operand object is passed implicitly using the this pointer.
*/