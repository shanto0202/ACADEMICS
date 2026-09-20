#include <iostream>
using namespace std;

const int SIZE = 10;

// generic array class
template <class AType>
class atype
{
    AType a[SIZE]; // array storing elements

public:
    atype()
    {
    }

    AType &operator[](int i); // overload [] operator
};

// range checking for array access
template <class AType>
AType &atype<AType>::operator[](int i)
{
    if (i < 0 || i > SIZE - 1)
    {
        cout << "\nIndex value of ";
        cout << i << " is out-of-bounds.\n";
        exit(1);
    }

    return a[i]; // return reference to element
}

int main()
{
    atype<int> intob;       // integer array
    atype<double> doubleob; // double array

    int i;

    cout << "Integer array: ";

    for (i = 0; i < SIZE; i++)
        intob[i] = i;

    for (i = 0; i < SIZE; i++)
        cout << intob[i] << " ";

    cout << '\n';

    cout << "Double array: ";

    for (i = 0; i < SIZE; i++)
        doubleob[i] = (double)i / 3;

    for (i = 0; i < SIZE; i++)
        cout << doubleob[i] << " ";

    cout << '\n';

    intob[12] = 100; // generates runtime error

    return 0;
}

/*
Key Notes:

1. Templates allow creation of generic data structures.
2. [] operator is overloaded to provide array-style access.
3. Range checking prevents invalid index access.
4. Same class works for int and double arrays.
*/