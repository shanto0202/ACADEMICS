// Demonstrate reverse.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{

    vector<int> v;

    unsigned int i;

    for (i = 0; i < 10; i++)
        v.push_back(i);

    cout << "Initial: ";

    for (i = 0; i < v.size(); i++)
        cout << v[i] << " ";

    cout << endl;

    reverse(v.begin(), v.end());

    cout << "Reversed: ";

    for (i = 0; i < v.size(); i++)
        cout << v[i] << " ";

    return 0;
}

/*
Key Notes
---------
reverse reverses order of elements.
Works on iterator range.
Complexity: O(n).
*/