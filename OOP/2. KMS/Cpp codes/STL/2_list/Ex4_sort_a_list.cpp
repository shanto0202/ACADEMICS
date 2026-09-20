// Sort a list.

#include <iostream>
#include <list>
#include <cstdlib>
using namespace std;

int main()
{
    list<int> lst;

    int i;

    // create a list of random integers
    for (i = 0; i < 10; i++)
        lst.push_back(rand());

    cout << "Original contents:\n";

    list<int>::iterator p = lst.begin();

    while (p != lst.end())
    {
        cout << *p << " ";
        p++;
    }

    cout << endl
         << endl;

    // sort the list
    lst.sort(); // sort list

    cout << "Sorted contents:\n";

    p = lst.begin();

    while (p != lst.end())
    {
        cout << *p << " ";
        p++;
    }

    return 0;
}

/*
Key Notes
---------
list.sort() sorts the list.
Sorting is done using merge sort internally.
Works because list elements are comparable.
*/