#include <iostream>
using namespace std;
class Shape
{
public:
    virtual void draw() = 0; // pure virtual
};
class derived : public Shape
{
public:
    void draw()
    {
        cout << "derived";
    }
};

int main()
{
    // Shape s; // ❌ ERROR
    Shape *s;
    derived d;
    d.draw();
}