#include <iostream>
using namespace std;

class Figure
{
    double dim1, dim2;

public:
    Figure(double a, double b)
    {
        dim1 = a;
        dim2 = b;
    }

    // pure virtual function
    virtual double area() = 0;

    // virtual function
    virtual void show()
    {
        cout << "Abstract";
    }

protected:
    double getDim1()
    {
        return dim1;
    }
    double getDim2()
    {
        return dim2;
    }
};

class Rectangle : public Figure
{
public:
    Rectangle(double a, double b) : Figure(a, b)
    {
    }

    double area()
    {
        return getDim1() * getDim2();
    }

    void show()
    {
        cout << "Rectangle Area: " << area();
    }
};

class Triangle : public Figure
{
public:
    Triangle(double a, double b) : Figure(a, b)
    {
    }

    double area()
    {
        return 0.5 * getDim1() * getDim2();
    }

    void show()
    {
        cout << "\nTriangle Area: " << area();
    }
};

int main()
{
    Rectangle r(4, 5);
    Triangle t(4, 3);

    Figure *figref;

    figref = &r;
    figref->show();

    figref = &t;
    figref->show();

    return 0;
}

/*
Output
Rectangle Area: 20
Triangle Area: 6


Key Notes:

1. Method overriding occurs when a derived class redefines a virtual function 
   of the base class.

2. Base class pointer can refer to derived class objects.

3. Virtual functions enable runtime polymorphism.

4. "= 0" makes a function a pure virtual function → abstract class.

5. The function called depends on the object type, not the pointer type.
*/