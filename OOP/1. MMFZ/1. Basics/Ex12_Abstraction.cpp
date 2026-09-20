// Demonstrates abstraction using abstract class and function overriding

#include <iostream>
using namespace std;

// Abstract class
class Figure
{
protected:
    double dim1, dim2;

public:
    Figure(double d1, double d2)
    {
        dim1 = d1;
        dim2 = d2;
    }

    // Pure virtual function (makes class abstract)
    virtual double area() = 0;
};

// Derived class Rectangle
class Rectangle : public Figure
{
public:
    Rectangle(double d1, double d2) : Figure(d1, d2) // constructor initializer
    {
    }

    double area()
    {
        return dim1 * dim2;
    }
};

// Derived class Triangle
class Triangle : public Figure
{
public:
    Triangle(double d1, double d2) : Figure(d1, d2) {}

    double area()
    {
        return dim1 * dim2 / 2;
    }
};

int main()
{
    Figure *p; // pointer to abstract class

    Rectangle r(10, 7);
    Triangle t(10, 5);
    //cout << r.area();

    p = &r;
    cout << "Rectangle Area: " << p->area() << endl;

    p = &t;
    cout << "Triangle Area: " << p->area() << endl;

    return 0;
}

/*
Key Notes:
1. Abstract class → class with at least one pure virtual function.
2. Pure virtual function: virtual double area() = 0;
3. Objects of abstract class cannot be created.
4. Derived classes must override the pure virtual function.
5. Demonstrates runtime polymorphism via base class pointer.
*/