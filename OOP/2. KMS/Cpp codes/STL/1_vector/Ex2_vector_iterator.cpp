#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

int main()
{
    vector<char> v(10);

    vector<char>::iterator p; // iterator declaration

    int i;

    p = v.begin(); // point to first element
    i = 0;

    // initialize vector using iterator
    while (p != v.end())
    {
        *p = i + 'a'; // assign value through iterator
        p++;
        i++;
    }

    cout << "Original contents:\n";

    p = v.begin();

    // display vector
    while (p != v.end())
    {
        cout << *p << " ";
        p++;
    }

    cout << "\n\n";

    // modify elements
    p = v.begin();

    while (p != v.end())
    {
        *p = toupper(*p);
        p++;
    }

    cout << "Modified Contents:\n";

    p = v.begin();

    while (p != v.end())
    {
        cout << *p << " ";
        p++;
    }

    cout << endl;

    return 0;
}

/*
Key Notes:

1. iterator behaves like a pointer to container elements.
2. begin() → first element of container.
3. end() → position after the last element.
4. *iterator accesses the element value.
5. Iterators are widely used with STL algorithms.
*/
