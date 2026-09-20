#include <iostream>
using namespace std;

// Base class
class NonGen
{
    int a;

public:
    NonGen(int x)
    {
        a = x;
    }

    void show()
    {
        cout << "NonGen: " << a << endl;
    }
};

// Generic class
template <class T>
class Gen : public NonGen
{
    T ob;

public:
    Gen(int x, T y) : NonGen(x)
    {
        ob = y;
    }

    void show()
    {
        cout << "Gen: " << ob << endl;
    }

    T getOb()
    {
        return ob;
    }
};

// Derived generic class
template <class T1, class T2>
class Gen2D : public Gen<T2>
{
    T1 ob1;

public:
    Gen2D(int x, T1 y, T2 z) : Gen<T2>(x, z)
    {
        ob1 = y;
    }

    void show()
    {
        cout << "Gen2D: " << this->getOb() << endl;
    }

    T2 getOb()
    {
        return Gen<T2>::getOb();
    }
};

int main()
{
    NonGen ob(10);
    Gen<char> ob1(20, 'A');
    Gen2D<double, char *> ob2(40, 60.5, (char *)"Gen2Object");

    ob.show();
    ob1.show();
    ob2.show();

    cout << ob1.getOb() << endl;
    cout << ob2.getOb() << endl;

    return 0;
}