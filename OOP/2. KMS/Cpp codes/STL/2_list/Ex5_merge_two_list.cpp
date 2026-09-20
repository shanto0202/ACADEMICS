// Merge two lists.

#include <iostream>
#include <list>
using namespace std;

int main()
{
    list<int> lst1, lst2;

    int i;

    for (i = 0; i < 4; i ++)
        lst1.push_back(i);

    for (i = 1; i < 4; i ++)
        lst2.push_back(i);
        
    // lst1.push_back(2);
    // lst1.push_back(6);
    // lst1.push_back(1);
    // lst1.push_back(5);

    // lst2.push_back(1);
    // lst2.push_back(6);
    // lst2.push_back(7);
    // lst2.push_back(0);
    // lst2.push_back(130);

    cout << "Contents of lst1:\n";

    list<int>::iterator p = lst1.begin();

    while (p != lst1.end())
    {
        cout << *p << " ";
        p++;
    }

    cout << endl
         << endl;

    cout << "Contents of lst2:\n";

    p = lst2.begin();

    while (p != lst2.end())
    {
        cout << *p << " ";
        p++;
    }

    cout << endl;

    // now merge the two lists
    lst1.merge(lst2);

    if (lst2.empty())
        cout << "lst2 is now empty\n";

    cout << "Contents of lst1 after merge:\n";

    p = lst1.begin();

    while (p != lst1.end())
    {
        cout << *p << " ";
        p++;
    }

    return 0;
}

/*
Key Notes
---------
merge() merges two sorted lists.
After merge, second list becomes empty.
Elements are transferred, not copied.
*/