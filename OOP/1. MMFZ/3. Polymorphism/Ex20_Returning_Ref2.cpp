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

    // WRONG design: returning reference for arithmetic operator
    Coord &operator+(Coord &ob)
    {
        Coord temp; // local object
        temp.x = x + ob.x;
        temp.y = y + ob.y;
        return temp; // returning reference to destroyed object
    }
};

int main()
{

    Coord a(10, 20), b(30, 40), c;
    int x, y;

    (a + b).getxy(x, y); // uses invalid temporary reference
    cout << x << " " << y << endl;

    c = a + b;
    c.getxy(x, y);
    cout << x << " " << y << endl;

    a.getxy(x, y);
    cout << x << " " << y << endl;

    b.getxy(x, y);
    cout << x << " " << y << endl;

    return 0;
}

/*
Key Notes:

1. Arithmetic operators (+, -, *, /, %) usually create a NEW object.
2. They should return object BY VALUE, not by reference.
3. Here operator+ returns Coord&, but temp is a local variable.
4. After the function ends, temp is destroyed.
5. The returned reference points to invalid memory → garbage value.
6. Correct implementation should be:
      Coord operator+(Coord &ob)
*/