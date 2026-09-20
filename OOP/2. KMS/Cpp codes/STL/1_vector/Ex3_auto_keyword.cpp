#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<char> v(10);

    int i = 0;

    // using auto to simplify iterator declaration
    for (auto p = v.begin(); p != v.end(); ++p)
    {
        *p = i + 'a';
        i++;
    }

    cout << "Original contents:\n";

    for (auto p = v.begin(); p != v.end(); ++p)
        cout << *p << " ";

    cout << "\n\n";

    return 0;
}

/*
Key Notes:

1. auto lets the compiler automatically determine variable type.
2. Commonly used with iterators.
3. Reduces long STL type declarations.
4. Introduced in C++11.
*/