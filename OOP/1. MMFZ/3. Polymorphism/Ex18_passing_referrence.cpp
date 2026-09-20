#include <iostream>
using namespace std;

class coord
{
    int x, y;

public:
    coord(int i = 0, int j = 0)
    {
        x = i;
        y = j;
    }

    // pass by reference to avoid copying object
    void getxy(int &i, int &j)
    {
        i = x;
        j = y;
    }

    // Binary + operator overloading
    // parameter passed by reference for efficiency
    coord operator+(coord &ob)
    {
        coord temp;
        temp.x = x + ob.x;
        temp.y = y + ob.y;
        return temp; // returns a temporary object
    }

    // Assignment operator overloading
    coord operator=(const coord &ob)
    {
        x = ob.x;
        y = ob.y;
        return *this; // return current object
    }
};

int main()
{

    coord a(10, 20), b(30, 40), c;
    int x, y;

    (a + b).getxy(x, y); // temporary object created from a+b
    cout << x << " " << y << endl;

    c = a = b; // assignment chaining from right ++,--,!=,+=,=
    c.getxy(x, y);
    cout << x << " " << y << endl;

    a.getxy(x, y);
    cout << x << " " << y << endl;

    return 0;
}

/*
Key Notes:

1. Reference parameter (coord &ob) avoids copying the whole object.
2. Passing reference is faster and memory efficient.
3. operator+ returns a temporary object (temp).
4. (a + b).getxy(x,y) works because the temporary object still exists for that statement.
5. operator= returns *this so assignment chaining like (c = a = b) works.
6. const is used in operator= to ensure the input object is not modified.
*/