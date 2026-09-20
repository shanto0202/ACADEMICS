#include <iostream>
using namespace std;

const int arraySize = 2;

class Point
{
    int *arr;

public:
    Point(int x = 0, int y = 0)
    {
        arr = new int[arraySize]; // dynamic array allocation
        arr[0] = x;
        arr[1] = y;
    }

    // overload [] operator
    int &operator[](int pos)
    {
        if (pos < arraySize) // check valid index
            return arr[pos]; // return reference to element
        else
        {
            cout << "Out of bound" << endl;
            exit(0);
        }
    }

    void print()
    {
        cout << "(" << arr[0] << "," << arr[1] << ")" << endl;
    }
};

int main()
{
    Point p1(3, 4);

    p1.print();

    p1[0] = 6; // uses overloaded []
    p1[1] = 8;

    p1.print();

    return 0;
}

/*
Key Notes:

1. operator[] allows object to be accessed like an array.
   Example: obj[index]

2. Returning reference (int&) allows modification:
      p1[0] = 6;

3. If return type was int (not reference),
   assignment like p1[0] = 6 would not work.

4. Bounds checking is added to avoid invalid access.

5. Used when class internally stores array-like data.
*/