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

    // Postfix ++  (object before operator)
    Coord operator++(int notused)
    {
        Coord temp = *this; // store original object
        x++;
        y++;
        return temp; // return old value
    }

    void show() const
    {
        cout << "(" << x << "," << y << ")" << endl;
    }
};

int main()
{

    Coord a(10, 20), b;

    b = a++; // postfix: first assign, then increment

    a.show();
    b.show();

    return 0;
}

/*
Output
(11,21)
(10,20)


Key Notes:

1. Unary operators work on a single object.
2. Prefix (++a) → object changes first, then value returned.
3. Postfix (a++) → original value returned, object updated later.
4. Postfix operator uses a dummy int parameter to distinguish it from prefix.
5. In postfix overloading:
      Coord operator++(int notused)
   returns the old object value.
*/