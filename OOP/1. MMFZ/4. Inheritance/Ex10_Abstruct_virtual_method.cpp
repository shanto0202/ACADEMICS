#include <iostream>
using namespace std;
class area
{ // abstract class
    double dim1, dim2;

public:
    void setarea(double d1, double d2)
    {
        dim1 = d1;
        dim2 = d2;
    }
    void getdim(double &d1, double &d2)
    {
        d1 = dim1;
        d2 = dim2;
    }
    virtual double getarea() = 0; // pure virtual
};

class rectangle : public area
{
public:
    double getarea()
    {
        double d1, d2;
        getdim(d1, d2);
        return d1 * d2;
    }
};

class triangle : public area
{
public:
    double getarea()
    {
        double d1, d2;
        getdim(d1, d2);
        return 0.5 * d1 * d2;
    }
};

int main()
{
    area *p; // area p; not allowed
    rectangle r;
    triangle t;
    r.setarea(3.3, 4.5);
    t.setarea(4.0, 5.0);
    p = &r;
    cout << r.getarea() << '\n';
    cout << p->getarea() << '\n';
    p = &t;
    cout << p->getarea() << '\n';
    return 0;
}

/*
Key Notes:

1. Pure virtual function makes area an abstract class.

2. Abstract class object cannot be created.

3. Base pointer is used for polymorphic behavior.

4. rectangle and triangle override getarea().
*/