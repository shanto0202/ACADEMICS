// Example 3: Using the whole std namespace

#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str;

    cout << "Enter a string: ";
    getline(cin, str);
    cout << str << endl;

    return 0;
}

/*
Key Notes:
1. Namespace → declarative region that organizes identifiers and avoids name conflicts.
2. std is the standard namespace in C++ (contains cout, cin, string, etc.).
3. Three ways to use namespace:
   a) std::identifier
   b) using std::identifier
   c) using namespace std
4. Scope resolution operator (::) accesses members of a namespace.
5. Namespaces prevent naming collisions between libraries or programs.
*/