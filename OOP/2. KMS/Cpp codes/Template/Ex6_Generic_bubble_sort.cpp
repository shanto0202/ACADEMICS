#include <iostream>
using namespace std;

// generic bubble sort
template <class X>
void bubble(X *items, int count)
{
    int a, b;
    X t; // temporary variable for swapping

    for (a = 1; a < count; a++)
    {
        for (b = count - 1; b >= a; b--)
        {
            if (items[b - 1] > items[b]) // compare adjacent elements
            {
                t = items[b - 1]; // swap
                items[b - 1] = items[b];
                items[b] = t;
            }
        }
    }
}

int main()
{
    int iarray[7] = {7, 5, 4, 3, 9, 8, 6};
    double darray[5] = {4.3, 2.5, -0.9, 100.2, 3.0};

    int i;

    cout << "Unsorted integer array: ";
    for (i = 0; i < 7; i++)
        cout << iarray[i] << " ";
    cout << endl;

    cout << "Unsorted double array: ";
    for (i = 0; i < 5; i++)
        cout << darray[i] << " ";
    cout << endl;

    bubble(iarray, 7); // sort int array
    bubble(darray, 5); // sort double array

    cout << "Sorted integer array: ";
    for (i = 0; i < 7; i++)
        cout << iarray[i] << " ";
    cout << endl;

    cout << "Sorted double array: ";
    for (i = 0; i < 5; i++)
        cout << darray[i] << " ";
    cout << endl;

    return 0;
}

/*
Key Notes:

1. Templates are very useful for generic algorithms.
2. Same bubble sort function works for different array types.
3. Here it is used for int and double arrays.
4. Data type changes, but sorting logic stays the same.
*/