// A simple map demonstration.

#include <iostream>
#include <map>
using namespace std;

int main()
{
    map<char, int> m;

    int i;

    // put pairs into map
    for (i = 0; i < 26; i++)
    {
        // m['A'+i] = 65+i;
        m.insert(pair<char, int>('A' + i, 65 + i));
        //m.insert('A' + i, 65 + i);
    }

    char ch;

    cout << "Enter key: ";
    cin >> ch;

    map<char, int>::iterator p;

    // find value given key
    p = m.find(ch);

    if (p != m.end())
        cout << "Its ASCII value is " << p->second;
    else
        cout << "Key not in map.\n";

    return 0;
}

/*
Key Notes
---------
map.insert() inserts key-value pair.
find() searches element by key.
iterator->second accesses value.
Keys automatically sorted.

The Map Template Class
----------------------
map is an associative container.
It stores key-value pairs.
Keys must be unique.
Example concept:

key -> value

'a' -> "alpha"
'g' -> "gamma"
'b' -> "beta"

If duplicate keys are needed, use multimap.
*/

/*
Key Notes
---------
map stores data as key-value pairs.
Keys are unique.
Elements are ordered by key.
Search complexity: O(log n).
*/