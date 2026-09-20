#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

// ---------------- Coord Class ----------------
class Coord
{
    int x, y;

public:
    Coord()
    {
    }

    Coord(int a, int b)
    {
        if (a <= 0 || a > 200 || b <= 0 || b > 200)
        {
            cout << "Invalid Coord\n";
            exit(1);
        }
        x = a;
        y = b;
    }

    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
};

// ---------------- Rectangle Class ----------------
class Rectangle
{
    Coord p1, p2, p3, p4;
    char *name;

    // distance between two points
    double dist(Coord a, Coord b)
    {
        return sqrt(pow(a.getX() - b.getX(), 2) + pow(a.getY() - b.getY(), 2));
    }

public:
    // (ii) constructor + right angle check
    Rectangle(Coord a, Coord b, Coord c, Coord d, const char *n)
    {
        // p1(a.getX(),a.getY());
        p1 = a;
        p2 = b;
        p3 = c;
        p4 = d;
        if (!isRightAngle(p1, p2, p3) || !isRightAngle(p2, p3, p4) || !isRightAngle(p3, p4, p1))
        {
            cout << "Not a rectangle\n";
            // exit(1);
        }
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }

    // static right angle check
    static bool isRightAngle(Coord a, Coord b, Coord c)
    {
        int x1 = a.getX() - b.getX();
        int y1 = a.getY() - b.getY();

        int x2 = c.getX() - b.getX();
        int y2 = c.getY() - b.getY();

        return (x1 * x2 + y1 * y2) == 0;
    }

    // (iii) length = larger side
    double length()
    {
        double l1 = dist(p1, p2);
        double l2 = dist(p2, p3);
        return max(l1, l2);
    }

    double width()
    {
        double l1 = dist(p1, p2);
        double l2 = dist(p2, p3);
        return min(l1, l2);
    }

    double perimeter()
    {
        return 2 * (length() + width());
    }

    double area()
    {
        return length() * width();
    }

    // (iv) square check
    bool square()
    {
        return length() == width();
    }

    // (v) clone constructor (copy constructor)
    Rectangle(const Rectangle &r) : p1(r.p1), p2(r.p2), p3(r.p3), p4(r.p4)
    {
        name = new char[strlen(r.name) + 1];
        strcpy(name, r.name);
    }

    // (vi) conversion operators
    operator int()
    {
        return (int)area();
    }

    operator string()
    {
        return string(name);
    }

    // (vii) assignment operator (deep copy)
    Rectangle &operator=(const Rectangle &r)
    {
        p1 = r.p1;
        p2 = r.p2;
        p3 = r.p3;
        p4 = r.p4;

        delete[] name;
        name = new char[strlen(r.name) + 1];
        strcpy(name, r.name);
        return *this;
    }

    ~Rectangle()
    {
        delete[] name;
    }
};

int main()
{
    return 0;
}