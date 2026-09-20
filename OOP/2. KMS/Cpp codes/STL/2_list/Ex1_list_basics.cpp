// List basics.
#include <iostream>
#include <list>
using namespace std;

int main()
{
    list<int> lst; // create an empty list

    int i;

    for (i = 0; i < 10; i++)
        lst.push_back(i); // insert elements

    cout << "Size = " << lst.size() << endl;

    cout << "Contents: ";

    list<int>::iterator p = lst.begin(); // iterator pointing to first element

    while (p != lst.end())
    {
        cout << *p << " "; // access element using iterator
        p++;
    }

    cout << "\n\n";

    // change contents of list
    p = lst.begin();

    while (p != lst.end())
    {
        *p = *p + 100; // modify element
        p++;
    }

    cout << "Contents modified: ";

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
push_back() inserts element at end.
begin() returns iterator to first element.
end() returns iterator after last element.
*iterator accesses element.
Elements of list can be modified via iterator.
*/