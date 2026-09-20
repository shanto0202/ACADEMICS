#include <iostream>
using namespace std;

// base template class
template <typename T>
class Box
{
protected:
    T value;

public:
    Box(T a)
    {
        value = a;
    }
    T get()
    {
        return value;
    }
};

// derived class using int specialization
class IntBox : public Box<int>
{
public:
    IntBox(int v) : Box<int>(v)
    {
        //   value = v;
    }

    int get() const
    {
        return value;
    }
};

template <class T>
class Box2 : public Box<T>
{
public:
    Box2(T v) : Box<T>(v)
    {
        //   value = v;
    }

    T get() const
    {
        return this->value;
    }
};

int main()
{
    IntBox a(10);
    Box b(10.10);
    Box2 c(10.30);
    cout << a.get() << endl;
    cout << b.get() << endl;
    cout << c.get();
}

/*
Key Notes:

1. Template classes can be inherited.
2. Derived class may specify the template type.
3. Example:
   class IntBox : public Box<int>
*/