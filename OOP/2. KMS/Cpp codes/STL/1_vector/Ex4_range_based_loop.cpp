#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<char> v(10), v2(3);
    int i = 0;

    for (auto &g : v2)
    {
        cin >> g;
    }

    // initialize vector
    for (auto p = v.begin(); p != v.end(); ++p)
    {
        // p[0
        *p = i + 'a';
        i++;
    }

    cout << "Original contents:\n";

    // range based loop

    // int q=v[i];
    for (auto q : v2)
        cout << q << " ";
    cout << "\n";

    for (auto q : v)
        cout << q << " ";

    cout << "\n\n";

    return 0;
}

/*
Key Notes:

1. Range-based loop simplifies iteration.
2. Syntax:
      for(auto element : container)
3. Automatically visits each element.
4. Introduced in C++11.
*/