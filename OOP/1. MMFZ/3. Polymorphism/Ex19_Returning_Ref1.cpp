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

    // assignment operator
    Coord &operator+=(Coord &ob);

    // stream operators must be friend functions
    friend ostream &operator<<(ostream &out, const Coord &ob)
    {
        // cout << "Helllo" << endl;
        out << "(" << ob.x << "," << ob.y << ")";
        return out; // return stream reference
    }
    friend istream &operator>>(istream &in, Coord &ob);

    // Prefix ++ : returns reference to modified object
    Coord &operator++()
    {
        ++x;
        ++y;
        return *this;
    }

    // Postfix ++ : returns copy of old object
    Coord operator++(int)
    {
        Coord temp = *this;
        x++;
        y++;
        return temp;
    }
};

// += operator implementation
Coord &Coord::operator+=(Coord &ob)
{
    x += ob.x;
    y += ob.y;
    return *this; // returning reference allows chaining
}

// >> operator
istream &operator>>(istream &in, Coord &ob)
{
    cout << "Enter coordinates (x y): ";
    in >> ob.x >> ob.y;
    return in; // return stream reference
}

int main()
{

    Coord a(10, 20), b;
    int x, y;

    cin >> b;
    cout << b << endl;

    a += b;
    cout << a << endl;

    return 0;
}

/*
Key Notes:

1. Assignment operators (+=, -=, etc.) should return reference (*this).
2. Prefix ++ returns reference to modified object.
3. Postfix ++ returns a copy of the object before modification.
4. Stream operators << and >> must return reference to stream.
5. Returning reference allows chaining operations.
   Example: a += b += c;
*/