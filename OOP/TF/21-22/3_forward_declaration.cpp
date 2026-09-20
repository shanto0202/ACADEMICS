#include <iostream>
using namespace std;

class B; // forward declaration

class A
{
public:
    void show(B *b)
    {
        cout << b->x;
    }
};

class B
{
public:
    int x = 10;
};

int main()
{
    A a;
    B b;
    a.show(&b);
}