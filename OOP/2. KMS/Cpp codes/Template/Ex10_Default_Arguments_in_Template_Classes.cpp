#include <iostream>
using namespace std;

// template with default type and size
template <class AType = int, int size = 10>
class atype
{
    AType a[size];
public:
    atype() {}

    AType &operator[](int i);
};

// range checking
template <class AType, int size>
AType &atype<AType, size>::operator[](int i)
{
    if (i < 0 || i > size - 1)
    {
        cout << "\nIndex value of ";
        cout << i << " is out-of-bounds.\n";
        exit(1);
    }
    return a[i];
}

int main()
{
    atype<int, 100> intarray;  // int array size 100
    atype<double> doublearray; // double array size 10 (default)
    atype<> defarray;          // int array size 10 (default)

    int i;

    cout << "int array: ";

    for (i = 0; i < 100; i++)
        intarray[i] = i;

    for (i = 0; i < 100; i++)
        cout << intarray[i] << " ";

    cout << '\n';

    cout << "double array: ";

    for (i = 0; i < 10; i++)
        doublearray[i] = (double)i / 3;

    for (i = 0; i < 10; i++)
        cout << doublearray[i] << " ";

    cout << '\n';

    cout << "defarray array: ";

    for (i = 0; i < 10; i++)
        defarray[i] = i;

    for (i = 0; i < 10; i++)
        cout << defarray[i] << " ";

    cout << '\n';

    return 0;
}

/*
Key Notes:

1. Template parameters can have default values.
2. Default type → int
3. Default size → 10
4. User may override defaults when creating objects.
*/