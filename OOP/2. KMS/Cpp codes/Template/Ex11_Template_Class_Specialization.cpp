#include <iostream>
using namespace std;

// generic template class
template <class T>
class myclass
{
    T x;

public:
    myclass(T a)
    {
        cout << "Inside generic myclass\n";
        x = a;
    }

    T getx()
    {
        return x;
    }
};

// explicit specialization for int
template <>
class myclass<int>
{
    int x;

public:
    myclass(int a)
    {
        cout << "Inside myclass<int> specialization\n";
        x = a * a; // special behavior
    }

    int getx()
    {
        return x;
    }
};

int main()
{
    myclass<double> d(10.1);
    cout << "double: " << d.getx() << "\n\n";

    myclass<int> i(5);
    cout << "int: " << i.getx() << "\n";

    return 0;
}

/*
Key Notes:

1. Template specialization allows custom behavior for specific types.
2. Syntax:
   template<>
3. Here int version behaves differently (square of value).
4. Generic version is used for other types.
*/