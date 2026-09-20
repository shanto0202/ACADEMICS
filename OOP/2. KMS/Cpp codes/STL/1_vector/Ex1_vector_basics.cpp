// Demonstrate a vector

#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

int main()
{
    vector<char> v(10); // create vector with 10 elements

    unsigned int i;

    // display initial size and capacity
    cout << "Size = " << v.size() << endl;
    cout << "Capacity = " << v.capacity() << endl;

    // assign characters
    for (i = 0; i < 10; i++)
        v[i] = i + 'a'; // store characters a,b,c,...

    cout << "Current Contents:\n";
    for (i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << "\n\n";

    cout << "Expanding vector\n";

    // add new elements at end
    for (i = 0; i < 5; i++)
        v.push_back(i + 10 + 'a');

    cout << "Size now = " << v.size() << endl;
    cout << "Capacity = " << v.capacity() << endl;

    cout << "Current contents:\n";
    for (i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << "\n";

    // modify elements
    for (i = 0; i < v.size(); i++)
        v[i] = toupper(v[i]);

    cout << "Modified Contents:\n";
    for (i = 0; i < v.size(); i++)
        cout << v[i] << " ";

    cout << endl;
}

/*
Key Notes:

1. vector is a dynamic array container in STL.
2. size() → number of elements stored.
3. capacity() → memory allocated for vector.
4. push_back() inserts elements at the end.
5. Vector automatically grows when needed.
6. Elements can be accessed using index like arrays.
*/
